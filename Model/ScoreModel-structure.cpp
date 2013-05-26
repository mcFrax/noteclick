#include "ScoreModel.h"

#include "SignalCommunication/ScoreChange.h"
#include "SignalCommunication/UserAction.h"

using namespace Model;

void ScoreModel::handleStructureChangeAction(const UserAction &action)
{
    switch (static_cast<UserAction::StructureChangeEnum>(action.action))
    {
    case UserAction::CreateGroup:          //(IdType parent_id)
        createGroup(action.args);
        return;
    case UserAction::CreateStaff:          //(IdType parent_id)
        createStaff(action.args);
        return;
    case UserAction::CreateVoice:          //(IdType parent_id)
        createVoice(action.args);
        return;
    case UserAction::MoveGroup:            //(IdType id, IdType new_parent_id)
        moveGroup(action.args);
        return;
    case UserAction::MoveStaff:            //(IdType id, IdType new_parent_id)
        moveGroup(action.args);
        return;
    case UserAction::MoveVoice:            //(IdType id, IdType new_parent_id)
        moveVoice(action.args);
        return;
    case UserAction::StructureObjectErase:  //(IdType id)
        eraseStructureObject(action.args);
        return;
    //Nie wstawiac default!
    //Chodzi o to, zeby dostac warn w przypadku nieobslugiwania czegos.
    }

    //Tu trafiamy tylko w przypadku niepoprawnej wartosci action.action:
    emit error(tr("Invalid or unhandled UserAction::action value (as UserAction::StructureChange) ")
            +QString::number(action.action));
}


void ScoreModel::createGroup(const VSA& arg)
{
    IdType parent_id;
    arg.unpackTo(parent_id);
    IdType id = IdRegisteredClass(reg).id(); // <brzydkie, ale chwilowo bedzie dzialac.
    emit changed(ScoreChange(ScoreChange::GroupCreated, vsa(id, parent_id)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}

void ScoreModel::createStaff(const VSA& arg)
{
    IdType parent_id;
    arg.unpackTo(parent_id);
    IdType id = IdRegisteredClass(reg).id(); // <brzydkie, ale chwilowo bedzie dzialac.
    emit changed(ScoreChange(ScoreChange::StaffCreated, vsa(id, parent_id)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}

void ScoreModel::createVoice(const VSA& arg)
{
    IdType parent_id;
    arg.unpackTo(parent_id);
    IdType id = IdRegisteredClass(reg).id(); // <brzydkie, ale chwilowo bedzie dzialac.
    emit changed(ScoreChange(ScoreChange::VoiceCreated, vsa(id, parent_id)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}

void ScoreModel::moveGroup(const VSA& arg)
{
    IdType id; IdType new_parent_id;
    arg.unpackTo(id, new_parent_id);
    emit changed(ScoreChange(ScoreChange::GroupMoved, vsa(id, new_parent_id)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}

void ScoreModel::moveStaff(const VSA& arg)
{
    IdType id; IdType new_parent_id;
    arg.unpackTo(id, new_parent_id);
    emit changed(ScoreChange(ScoreChange::StaffMoved, vsa(id, new_parent_id)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}

void ScoreModel::moveVoice(const VSA& arg)
{
    IdType id; IdType new_parent_id;
    arg.unpackTo(id, new_parent_id);
    emit changed(ScoreChange(ScoreChange::VoiceMoved, vsa(id, new_parent_id)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}

void ScoreModel::eraseStructureObject(const VSA& arg)
{
    IdType id;
    arg.unpackTo(id);
    emit changed(ScoreChange(ScoreChange::StructureObjectErased, vsa(id)));
    emit warning(tr("Not fully handled action")+" ("+__func__+")");
}
