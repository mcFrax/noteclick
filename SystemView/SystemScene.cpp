#include "SystemScene.h"
#include "SystemImageItem.h"

#include <QPixmap>
#include <QState>
#include <QString>

#include "AddStaffState.h"

using namespace SystemView;

SystemScene::SystemScene(QObject *parent) :
    QGraphicsScene(parent)
{
    handlersVal = 0;
    setupMachine();

    #warning tymczasowe id dla SystemScene
    registerIn(idReg);
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

    statesVal.editSystem->setInitialState(statesVal.normalCursor);
    stateMachine.addState(statesVal.editSystem);

    stateMachine.setInitialState(statesVal.editSystem);
    stateMachine.start();
}

const SceneEventHandlers *SystemScene::handlers() const
{
    return handlersVal;
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
            //To nas nie obchodzi.
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


void SystemScene::handleSystemChanged(ScoreChange change)
{
    switch (static_cast<ScoreChange::SystemChangeEnum>(change.change))
    {
        case ScoreChange::SystemImageCreated:   //(IdType systemId, IdType systemImageId, SystemImageInfo sysImgInfo)
        case ScoreChange::StaffSystemCreated:   //(IdType id, IdType systemImageId, StaffPosition position)
        case ScoreChange::ClefCreated:          //(IdType id, IdType staffId, StaffCoords coords, ClefType clefType)
        case ScoreChange::KeySignatureCreated:  //(IdType id, IdType staffId, StaffCoords coords, KeySignature signature)
        case ScoreChange::TimeSignatureCreated: //(IdType id, IdType staffId, StaffCoords coords, TimeSignature signature)
        case ScoreChange::NoteCreated:          //(IdType id, IdType staffId, StaffCoords coords, IdType voiceId, NoteValue noteValue)
        case ScoreChange::PauseCreated:         //(IdType id, IdType staffId, StaffCoords coords, IdType voiceId, NoteValue pauseValue)
        case ScoreChange::BarcheckCreated:      //(IdType id, IdType staffId, StaffCoords coords)
        case ScoreChange::SynchroMarkCreated:   //(IdType id, IdType staffId, StaffCoords coords, IdType synchroId)
        case ScoreChange::SlurCreated:          //(IdType id, IdType noteId1, IdType noteId2)

        case ScoreChange::StaffSystemMoved:     //(IdType staffId, StaffPosition new_position)
        case ScoreChange::ClefMoved:            //(IdType clefId, StaffCoords new_coords)
        case ScoreChange::KeySignatureMoved:    //(IdType keySignId, StaffCoords coords)
        case ScoreChange::TimeSignatureMoved:   //(IdType timeSignId, StaffCoords coords)
        case ScoreChange::NoteMoved:            //(IdType noteId, StaffCoords coords)
        case ScoreChange::PauseMoved:           //(IdType pauseId, StaffCoords coords)
        case ScoreChange::BarcheckMoved:        //(IdType barcheckId, StaffCoords coords)
        case ScoreChange::SynchroMarkMoved:     //(IdType synchroMarkId, StaffCoords coords)

        case ScoreChange::ClefTypeChanged:      //(IdType clefId, ClefType new_clefType)
        case ScoreChange::KeySignatureChanged:  //(IdType keySignId, KeySignature new_signature)
        case ScoreChange::TimeSignatureChanged: //(IdType timeSignId, TimeSignature new_signature)
        case ScoreChange::NoteValueChanged:     //(IdType noteId, NoteValue new_noteValue)
        case ScoreChange::PauseValueChanged:    //(IdType pauseId, NoteValue new_pauseValue)
        case ScoreChange::SynchroMarkIdChanged: //(IdType synchroMarkId, IdType new_synchroId)

        case ScoreChange::SystemObjectErased:    //(IdType objectId)
            emit warning(tr("Not handled system change"));
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
