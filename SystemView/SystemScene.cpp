#include "SystemScene.h"
#include "SystemImageItem.h"

#include <QPixmap>
#include <QState>
#include <QString>

#include "AddStaffState.h"
#include "SystemImageInfo.h"
#include "AddStaffState.h"
#include "AddClefState.h"
#include "AddNoteState.h"
#include "StaffSystemItem.h"
#include "ClefItem.h"
#include "NoteItem.h"
#include "VoiceElementItem.h"

using namespace SystemView;

SystemScene::SystemScene(QObject *parent) :
    QGraphicsScene(parent)
{
    currentVoiceVal = noneId;
    handlersVal = 0;
    setupMachine();

    #warning tymczasowe id dla SystemScene
    registerIn(idReg, 1000000);
}

SystemScene::~SystemScene()
{
    idReg.unregister(this);
}

const SystemScene::MachineStates &SystemScene::states() const
{
    return statesVal;
}


void SystemScene::setupMachine()
{
    statesVal.editSystem = new QState();
    statesVal.normalCursor = new QState(statesVal.editSystem);
    statesVal.addStaff = new AddStaffState(statesVal.editSystem, this);
    statesVal.addClef = new AddClefState(statesVal.editSystem, this);
    statesVal.addNote = new AddNoteState(statesVal.editSystem, this);

    statesVal.editSystem->setInitialState(statesVal.normalCursor);
    stateMachine.addState(statesVal.editSystem);

    stateMachine.setInitialState(statesVal.editSystem);
    stateMachine.start();
}

const SceneEventHandlers *SystemScene::handlers() const
{
    return handlersVal;
}

IdType SystemScene::currentVoice() const
{
    return currentVoiceVal;
}

void SystemScene::setHandlers(const SceneEventHandlers * handlers)
{
    handlersVal = handlers;
}

void SystemScene::scoreChange(ScoreChange change)
{
    //sprawdzenie, czy dotyczy biezacego systemu
    if (change.affectedSystem != id() && change.affectedSystem != anyId)
            return;

    try
    {
        switch (change.category)
        {
        case ScoreChange::StructureChanged:
            handleStructureChanged(change);
            return;
        case ScoreChange::SystemChanged:
            handleSystemChanged(change);
            return;
        case ScoreChange::ScoreChanged:
            handleScoreChanged(change);
            return;
        //Nie wstawiac default!
        //Chodzi o to, zeby dostac warn w przypadku nieobslugiwania czegos.
        }

        //Tu trafiamy tylko w przypadku niepoprawnej wartosci action.category:
        emit error(tr("Invalid ScoreChange::category value ")+QString::number(change.category));
    }
    catch (std::bad_cast &e)
    {
        emit error(tr("std::bad_cast caught during ScoreChange handling: ")+e.what()+'\n'
                   +"VSA typeid = "+change.args.typeName());
    }
}

void SystemScene::selectVoice(IdType voiceId)
{
    if (currentVoiceVal == voiceId) return;

    for (auto item : voiceElements[currentVoiceVal])
        item->setState(VoiceElementItem::InactiveVoice);
    currentVoiceVal = voiceId;
    for (auto item : voiceElements[currentVoiceVal])
        item->setState(VoiceElementItem::ActiveVoice);
}

void SystemScene::voiceVisible(IdType voiceId, bool visible)
{
    for (auto item : voiceElements[voiceId])
        item->setVisible(visible);
}


void SystemScene::handleStructureChanged(ScoreChange change)
{
    if (change.change == ScoreChange::StructureObjectErased){
        int id;
        change.args.unpackTo(id);
        if (id == currentVoice())
            currentVoiceVal = noneId;
    }
}

void SystemScene::handleSystemChanged(ScoreChange change)
{
    switch (static_cast<ScoreChange::SystemChangeEnum>(change.change))
    {
        case ScoreChange::SystemImageCreated:   //(IdType systemId, IdType systemImageId, SystemImageInfo sysImgInfo)
            systemImageCreated(change);
            return;
        case ScoreChange::StaffSystemCreated:   //(IdType id, IdType systemImageId, StaffPosition position)
            staffSystemCreated(change);
            return;
        case ScoreChange::ClefCreated:          //(IdType id, IdType staffId, StaffCoords coords, ClefInfo clefInfo)
            clefCreated(change);
            return;
        case ScoreChange::KeySignatureCreated:  //(IdType id, IdType staffId, StaffCoords coords, KeySignature signature)
        case ScoreChange::TimeSignatureCreated: //(IdType id, IdType staffId, StaffCoords coords, TimeSignature signature)
            return;
        case ScoreChange::NoteCreated:          //(IdType id, IdType staffId, StaffCoords coords, IdType voiceId, NoteValue noteValue)
            noteCreated(change);
            return;
        case ScoreChange::RestCreated:         //(IdType id, IdType staffId, StaffCoords coords, IdType voiceId, NoteValue restValue)
        case ScoreChange::BarcheckCreated:      //(IdType id, IdType staffId, StaffCoords coords)
        case ScoreChange::SynchroMarkCreated:   //(IdType id, IdType staffId, StaffCoords coords, IdType synchroId)
        case ScoreChange::SlurCreated:          //(IdType id, IdType noteId1, IdType noteId2)

        case ScoreChange::StaffSystemMoved:     //(IdType staffId, StaffPosition new_position)
        case ScoreChange::ClefMoved:            //(IdType clefId, StaffCoords new_coords)
        case ScoreChange::KeySignatureMoved:    //(IdType keySignId, StaffCoords coords)
        case ScoreChange::TimeSignatureMoved:   //(IdType timeSignId, StaffCoords coords)
        case ScoreChange::NoteMoved:            //(IdType noteId, StaffCoords coords)
        case ScoreChange::RestMoved:           //(IdType restId, StaffCoords coords)
        case ScoreChange::BarcheckMoved:        //(IdType barcheckId, StaffCoords coords)
        case ScoreChange::SynchroMarkMoved:     //(IdType synchroMarkId, StaffCoords coords)

        case ScoreChange::ClefChanged:      //(IdType clefId, ClefInfo new_clefInfo)
        case ScoreChange::KeySignatureChanged:  //(IdType keySignId, KeySignature new_signature)
        case ScoreChange::TimeSignatureChanged: //(IdType timeSignId, TimeSignature new_signature)
        case ScoreChange::NoteValueChanged:     //(IdType noteId, NoteValue new_noteValue)
        case ScoreChange::RestValueChanged:    //(IdType restId, NoteValue new_restValue)
        case ScoreChange::SynchroMarkIdChanged: //(IdType synchroMarkId, IdType new_synchroId)

        case ScoreChange::SystemObjectErased:    //(IdType objectId)
            emit warning(tr("Not handled system change")+" ("+__func__+")");
            return;

        //Nie wstawiac default!
        //Chodzi o to, zeby dostac warn w przypadku nieobslugiwania czegos.
    }

    //Tu trafiamy tylko w przypadku niepoprawnej wartosci action.action:
    emit error(tr("Invalid or unhandled ScoreChanged::change value (as ScoreChanged::SystemChanged) ")
            +QString::number(change.change));
}

void SystemScene::handleScoreChanged(ScoreChange change)
{
    switch (static_cast<ScoreChange::ScoreChangeEnum>(change.change))
    {
    case ScoreChange::TitleChanged:           //(QString new_title)
        return;


    //tutaj trzeba bedzie obsluzyc usuniecie biezacego systemu


    //Nie wstawiac default!
    //Chodzi o to, zeby dostac warn w przypadku nieobslugiwania czegos.
    }

    //Tu trafiamy tylko w przypadku niepoprawnej wartosci action.action:
    emit error(tr("Invalid or unhandled ScoreChanged::change value (as ScoreChanged::ScoreChanged) ")
               +QString::number(change.change));
}

void SystemScene::systemImageCreated(const ScoreChange &change)
{
    IdType id; IdType sysId; SystemImageInfo info;

    change.args.unpackTo(id, sysId, info);

    if (sysId != this->id()){
        emit warning(tr("Inconsistent ScoreChange (sysId != this->id())"));
        return;
    }

    QPixmap pixmap = info.pixmap();

    if (pixmap.isNull()){
        emit error(tr("Nie udało się otworzyć pliku: ")+'"'+info.fileName()+'"');
        return;
    }

    SystemImageItem* newSystem = new SystemImageItem(idReg, id, pixmap);
    if (!systemImageItems.empty())
        newSystem->setOffset(0, systemImageItems.back()->boundingRect().bottom());
    systemImageItems.push_back(newSystem);
    addItem(newSystem);
}

void SystemScene::staffSystemCreated(const ScoreChange &change)
{
    IdType id; IdType systemImageId; StaffPosition position;

    change.args.unpackTo(id, systemImageId, position);

    SystemImageItem* system = idReg.ptrAs<SystemImageItem>(systemImageId);
    if (!system){
        emit error(QString(__PRETTY_FUNCTION__)+':'+tr("Incorrect id"));
        return;
    }

    new StaffSystemItem(idReg, id, position, system);
}

void SystemScene::clefCreated(const ScoreChange &change)
{
    IdType id; IdType staffId; StaffCoords coords; ClefInfo clefInfo;

    change.args.unpackTo(id, staffId, coords, clefInfo);

    StaffSystemItem* staff = idReg.ptrAs<StaffSystemItem>(staffId);
    if (!staff){
        emit error(QString(__PRETTY_FUNCTION__)+':'+tr("Incorrect id"));
        return;
    }

    new ClefItem(idReg, id, coords, clefInfo, staff);
}

void SystemScene::noteCreated(const ScoreChange &change)
{
    IdType id; IdType staffId; StaffCoords coords; IdType voiceId; NoteValue noteValue;

    change.args.unpackTo(id, staffId, coords, voiceId, noteValue);

    StaffSystemItem* staff = idReg.ptrAs<StaffSystemItem>(staffId);
    if (!staff){
        emit error(QString(__PRETTY_FUNCTION__)+':'+tr("Incorrect id"));
        return;
    }

    new NoteItem(idReg, id, voiceId, staff, noteValue, coords);
}

void SystemScene::registerVoiceElement(IdType voiceId, VoiceElementItem *item)
{
    voiceElements[voiceId][item->id()] = item;
}

void SystemScene::unregisterVoiceElement(IdType voiceId, VoiceElementItem *item)
{
    voiceElements[voiceId].remove(item->id());
}
