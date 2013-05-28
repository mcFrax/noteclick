#include "ScoreModel.h"

#include "StaffCoords.h"
#include "SignalCommunication/ScoreChange.h"
#include "SignalCommunication/UserAction.h"

#include "SystemImageInfo.h"
#include "ClefInfo.h"
#include "NoteValue.h""

//tymczasowe definicje niegotowych typów
#warning temp KeySignature & TimeSignature
typedef int KeySignatureInfo;
typedef int TimeSignatureInfo;

using namespace Model;

void ScoreModel::handleSystemChangeAction(const UserAction &action)
{
    switch (static_cast<UserAction::SystemChangeEnum>(action.action))
    {
    case UserAction::CreateSystemImage:   //(IdType systemId, SystemImageInfo sysImgInfo)
        createSystemImage(action.args);
        return;
    case UserAction::CreateStaffSystem:   //(IdType systemImageId, StaffPosition position)
        createStaffSystem(action.args);
        return;
    case UserAction::CreateClef:          //(IdType staffId, StaffCoords coords, ClefInfo clefInfo)
        createClef(action.args);
        return;
    case UserAction::CreateKeySignature:  //(IdType staffId, StaffCoords coords, KeySignature signature)
        createKeySignature(action.args);
        return;
    case UserAction::CreateTimeSignature: //(IdType staffId, StaffCoords coords, TimeSignature signature)
        createTimeSignature(action.args);
        return;
    case UserAction::CreateNote:          //(IdType staffId, StaffCoords coords, IdType voiceId, NoteValue noteValue)
        createNote(action.args);
        return;
    case UserAction::CreateRest:         //(IdType staffId, StaffCoords coords, IdType voiceId, NoteValue restValue)
        createRest(action.args);
        return;
    case UserAction::CreateBarcheck:      //(IdType staffId, StaffCoords coords)
        createBarcheck(action.args);
        return;
    case UserAction::CreateSynchroMark:   //(IdType staffId, StaffCoords coords, IdType synchroId)
        createSynchroMark(action.args);
        return;
    case UserAction::CreateSlur:          //(IdType noteId1, IdType noteId2)
        createSlur(action.args);
        return;

    case UserAction::MoveStaffSystem:     //(IdType staffId, StaffPosition new_position)
        moveStaffSystem(action.args);
        return;
    case UserAction::MoveClef:            //(IdType clefId, StaffCoords new_coords)
        moveClef(action.args);
        return;
    case UserAction::MoveKeySignature:    //(IdType keySignId, StaffCoords coords)
        moveKeySignature(action.args);
        return;
    case UserAction::MoveTimeSignature:   //(IdType timeSignId, StaffCoords coords)
        moveTimeSignature(action.args);
        return;
    case UserAction::MoveNote:            //(IdType noteId, StaffCoords coords)
        moveNote(action.args);
        return;
    case UserAction::MoveRest:           //(IdType restId, StaffCoords coords)
        moveRest(action.args);
        return;
    case UserAction::MoveBarcheck:        //(IdType barcheckId, StaffCoords coords)
        moveBarcheck(action.args);
        return;
    case UserAction::MoveSynchroMark:     //(IdType synchroMarkId, StaffCoords coords)
        moveSynchroMark(action.args);
        return;

    case UserAction::ChangeClef:      //(IdType clefId, ClefInfo new_clefInfo)
        ChangeClef(action.args);
        return;
    case UserAction::ChangeKeySignature:  //(IdType keySignId, KeySignature new_signature)
        changeKeySignature(action.args);
        return;
    case UserAction::ChangeTimeSignature: //(IdType timeSignId, TimeSignature new_signature)
        changeTimeSignature(action.args);
        return;
    case UserAction::ChangeNoteValue:     //(IdType noteId, NoteValue new_noteValue)
        changeNoteValue(action.args);
        return;
    case UserAction::ChangeRestValue:    //(IdType restId, NoteValue new_restValue)
        changeRestValue(action.args);
        return;
    case UserAction::ChangeSynchroMarkId: //(IdType synchroMarkId, IdType new_synchroId)
        changeSynchroMarkId(action.args);
        return;

    case UserAction::EraseSystemObject:    //(IdType objectId)
        eraseSystemObject(action.args);
        return;
    //Nie wstawiac default!
    //Chodzi o to, zeby dostac warn w przypadku nieobslugiwania czegos.
    }

    //Tu trafiamy tylko w przypadku niepoprawnej wartosci action.action:
    emit error(tr("Invalid or unhandled UserAction::action value (as UserAction::SystemChange) ")
            +QString::number(action.action));
}


void ScoreModel::createSystemImage(const VSA &arg)
{
    IdType systemId; SystemImageInfo info;
    arg.unpackTo(systemId, info);
    IdType id = IdRegisteredClass(reg).id(); // <brzydkie, ale chwilowo bedzie dzialac.
    emit changed(ScoreChange(ScoreChange::SystemImageCreated, vsa(id, systemId, info), systemId));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}

void ScoreModel::createStaffSystem(const VSA& arg)
{
    IdType systemImageId; StaffPosition position;
    arg.unpackTo(systemImageId, position);
    IdType id = IdRegisteredClass(reg).id(); // <brzydkie, ale chwilowo bedzie dzialac.
    emit changed(ScoreChange(ScoreChange::StaffSystemCreated, vsa(id, systemImageId, position)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}

void ScoreModel::createClef(const VSA& arg)
{
    IdType staffId; StaffCoords coords; ClefInfo clefInfo;
    arg.unpackTo(staffId, coords, clefInfo);
    IdType id = IdRegisteredClass(reg).id(); // <brzydkie, ale chwilowo bedzie dzialac.
    coords.setY(clefInfo.positionOnStaff()/8.0);
    emit changed(ScoreChange(ScoreChange::ClefCreated, vsa(id, staffId, coords, clefInfo)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}

void ScoreModel::createKeySignature(const VSA& arg)
{
    IdType staffId; StaffCoords coords; ::KeySignatureInfo signature;
    arg.unpackTo(staffId, coords, signature);
    IdType id = IdRegisteredClass(reg).id(); // <brzydkie, ale chwilowo bedzie dzialac.
    emit changed(ScoreChange(ScoreChange::KeySignatureCreated, vsa(id, staffId, coords, signature)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}

void ScoreModel::createTimeSignature(const VSA& arg)
{
    IdType staffId; StaffCoords coords; ::TimeSignatureInfo signature;
    arg.unpackTo(staffId, coords, signature);
    IdType id = IdRegisteredClass(reg).id(); // <brzydkie, ale chwilowo bedzie dzialac.
    emit changed(ScoreChange(ScoreChange::TimeSignatureCreated, vsa(id, staffId, coords, signature)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}

void ScoreModel::createNote(const VSA& arg)
{
    //(IdType staffId, StaffCoords coords, IdType voiceId, NoteValue noteValue)
    IdType staffId; StaffCoords coords; IdType voiceId; NoteValue noteValue;
    arg.unpackTo(staffId, coords, voiceId, noteValue);
    IdType id = IdRegisteredClass(reg).id(); // <brzydkie, ale chwilowo bedzie dzialac.
    emit changed(ScoreChange(ScoreChange::NoteCreated, vsa(id, staffId, coords.roundedToDegree(), voiceId, noteValue)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}

void ScoreModel::createRest(const VSA& arg)
{
    IdType staffId; StaffCoords coords; IdType voiceId; NoteValue restValue;
    arg.unpackTo(staffId, coords, voiceId, restValue);
    IdType id = IdRegisteredClass(reg).id(); // <brzydkie, ale chwilowo bedzie dzialac.
    emit changed(ScoreChange(ScoreChange::RestCreated, vsa(id, staffId, coords, voiceId, restValue)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}

void ScoreModel::createBarcheck(const VSA& arg)
{
    IdType staffId; StaffCoords coords;
    arg.unpackTo(staffId, coords);
    IdType id = IdRegisteredClass(reg).id(); // <brzydkie, ale chwilowo bedzie dzialac.
    emit changed(ScoreChange(ScoreChange::BarcheckCreated, vsa(id, staffId, coords)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}

void ScoreModel::createSynchroMark(const VSA& arg)
{
    IdType staffId; StaffCoords coords; IdType synchroId;
    arg.unpackTo(staffId, coords, synchroId);
    IdType id = IdRegisteredClass(reg).id(); // <brzydkie, ale chwilowo bedzie dzialac.
    emit changed(ScoreChange(ScoreChange::SynchroMarkCreated, vsa(id, staffId, coords, synchroId)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}

void ScoreModel::createSlur(const VSA& arg)
{
    IdType noteId1; IdType noteId2;
    arg.unpackTo(noteId1, noteId2);
    IdType id = IdRegisteredClass(reg).id(); // <brzydkie, ale chwilowo bedzie dzialac.
    emit changed(ScoreChange(ScoreChange::SlurCreated, vsa(id, noteId1, noteId2)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}


void ScoreModel::moveStaffSystem(const VSA& arg)
{
    IdType staffId; StaffPosition newPosition;
    arg.unpackTo(staffId, newPosition);
    emit changed(ScoreChange(ScoreChange::StaffSystemMoved, vsa(staffId, newPosition)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}

void ScoreModel::moveClef(const VSA& arg)
{
    IdType clefId; StaffCoords newCoords;
    arg.unpackTo(clefId, newCoords);
    emit changed(ScoreChange(ScoreChange::ClefMoved, vsa(clefId, newCoords)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}

void ScoreModel::moveKeySignature(const VSA& arg)
{
    IdType keySignId; StaffCoords newCoords;
    arg.unpackTo(keySignId, newCoords);
    emit changed(ScoreChange(ScoreChange::KeySignatureMoved, vsa(keySignId, newCoords)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}

void ScoreModel::moveTimeSignature(const VSA& arg)
{
    IdType timeSignId; StaffCoords newCoords;
    arg.unpackTo(timeSignId, newCoords);
    emit changed(ScoreChange(ScoreChange::TimeSignatureMoved, vsa(timeSignId, newCoords)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}

void ScoreModel::moveNote(const VSA& arg)
{
    IdType noteId; StaffCoords coords;
    arg.unpackTo(noteId, coords);
    emit changed(ScoreChange(ScoreChange::NoteMoved, vsa(noteId, coords.roundedToDegree())));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}

void ScoreModel::moveRest(const VSA& arg)
{
    IdType restId; StaffCoords coords;
    arg.unpackTo(restId, coords);
    emit changed(ScoreChange(ScoreChange::RestMoved, vsa(restId, coords)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}

void ScoreModel::moveBarcheck(const VSA& arg)
{
    IdType barcheckId; StaffCoords coords;
    arg.unpackTo(barcheckId, coords);
    emit changed(ScoreChange(ScoreChange::BarcheckMoved, vsa(barcheckId, coords)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}

void ScoreModel::moveSynchroMark(const VSA& arg)
{
    IdType synchroMarkId; StaffCoords coords;
    arg.unpackTo(synchroMarkId, coords);
    emit changed(ScoreChange(ScoreChange::SynchroMarkMoved, vsa(synchroMarkId, coords)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}


void ScoreModel::ChangeClef(const VSA& arg)
{
    IdType clefId; ClefInfo new_clefInfo;
    arg.unpackTo(clefId, new_clefInfo);
    emit changed(ScoreChange(ScoreChange::ClefChanged, vsa(clefId, new_clefInfo)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}

void ScoreModel::changeKeySignature(const VSA& arg)
{
    IdType keySignId; ::KeySignatureInfo new_signature;
    arg.unpackTo(keySignId, new_signature);
    emit changed(ScoreChange(ScoreChange::KeySignatureChanged, vsa(keySignId, new_signature)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}

void ScoreModel::changeTimeSignature(const VSA& arg)
{
    IdType timeSignId; ::TimeSignatureInfo new_signature;
    arg.unpackTo(timeSignId, new_signature);
    emit changed(ScoreChange(ScoreChange::TimeSignatureChanged, vsa(timeSignId, new_signature)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}

void ScoreModel::changeNoteValue(const VSA& arg)
{
    IdType noteId; NoteValue new_noteValue;
    arg.unpackTo(noteId, new_noteValue);
    emit changed(ScoreChange(ScoreChange::NoteValueChanged, vsa(noteId, new_noteValue)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}

void ScoreModel::changeRestValue(const VSA& arg)
{
    IdType restId; NoteValue new_noteValue;
    arg.unpackTo(restId, new_noteValue);
    emit changed(ScoreChange(ScoreChange::RestValueChanged, vsa(restId, new_noteValue)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}

void ScoreModel::changeSynchroMarkId(const VSA& arg)
{
    IdType synchroMarkId; IdType new_synchroId;
    arg.unpackTo(synchroMarkId, new_synchroId);
    emit changed(ScoreChange(ScoreChange::SynchroMarkIdChanged, vsa(synchroMarkId, new_synchroId)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}


void ScoreModel::eraseSystemObject(const VSA& arg)
{
    IdType objectId;
    arg.unpackTo(objectId);
    emit changed(ScoreChange(ScoreChange::SystemObjectErased, vsa(objectId)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}
