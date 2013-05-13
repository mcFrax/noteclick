#include "ScoreModel.h"

#include "SignalCommunication/ScoreChange.h"
#include "SignalCommunication/UserAction.h"

#include <stdexcept>

using namespace Model;

ScoreModel::ScoreModel(QObject *parent) :
    QObject(parent)
{
}


void ScoreModel::userAction(UserAction action)
{
    try
    {
        switch (action.category)
        {
        case UserAction::StructureChange:
            handleStructureChangeAction(action);
            return;
        case UserAction::SystemChange:
            handleSystemChangeAction(action);
            return;
        case UserAction::ScoreChange:
            handleGlobalChangeAction(action);
            return;
        //Nie wstawiac default!
        //Chodzi o to, zeby dostac warn w przypadku nieobslugiwania czegos.
        }

        //Tu trafiamy tylko w przypadku niepoprawnej wartosci action.category:
        emit error(tr("Invalid UserAction::category value ")+QString::number(action.category));
    }
    catch (std::bad_cast &e)
    {
        emit error(tr("std::bad_cast caught during action handling: ")+e.what());
    }
}

void ScoreModel::handleGlobalChangeAction(const UserAction &action)
{
    switch (static_cast<UserAction::ScoreChangeEnum>(action.action))
    {
    case UserAction::ChangeTitle:           //(QString new_title)
        changeTitle(action.args);
        return;
    //Nie wstawiac default!
    //Chodzi o to, zeby dostac warn w przypadku nieobslugiwania czegos.
    }

    //Tu trafiamy tylko w przypadku niepoprawnej wartosci action.action:
    emit error(tr("Invalid or unhandled UserAction::action value (as UserAction::ScoreChange) ")
            +QString::number(action.action));
}

void ScoreModel::changeTitle(const VSA& arg)
{
    QString new_title;
    arg.unpackTo(new_title);
    emit changed(ScoreChange(ScoreChange::GroupCreated, vsa(new_title)));
    emit warning(tr("Not fully handled action"));
}
