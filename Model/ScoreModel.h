#ifndef SCOREMODEL_H
#define SCOREMODEL_H

#include <QObject>

#include "IdRegisteredClass.h"
#include "VersatileSlotArgument.h"
#include "SignalCommunication/ScoreChange.h"
#include "SignalCommunication/UserAction.h"
#include "StructureModels.h"
#include "SystemModels.h"

namespace Model
{

class ScoreModel : public QObject, protected IdRegisteredClass
{
    Q_OBJECT
    friend class ModelBase;
public:
    explicit ScoreModel(QObject *parent = 0);
    
    static const IdType ScoreId;
signals:
    void changed(ScoreChange change);

    void error(QString what); //byc moze trzeba jakos rozdzielic fatal error/non-fatal error
    void warning(QString what);
    void notice(QString what);
    
public slots:
    void userAction(UserAction action);

private:
    Reg reg;

    void handleStructureChangeAction(const UserAction& action);
    void handleSystemChangeAction(const UserAction& action);
    void handleGlobalChangeAction(const UserAction& action);

    void createGroup(const VSA& arg);
    void createStaff(const VSA& arg);
    void createVoice(const VSA& arg);
    void moveGroup(const VSA& arg);
    void moveStaff(const VSA& arg);
    void moveVoice(const VSA& arg);

    void eraseStructureObject(const VSA& arg);
    void renameStructureObject(const VSA& arg);


    void createSystemImage(const VSA& arg);
    void createStaffSystem(const VSA& arg);
    void createClef(const VSA& arg);
    void createKeySignature(const VSA& arg);
    void createTimeSignature(const VSA& arg);
    void createNote(const VSA& arg);
    void createRest(const VSA& arg);
    void createBarcheck(const VSA& arg);
    void createSynchroMark(const VSA& arg);
    void createSlur(const VSA& arg);
    void createSystem(const VSA& arg);


    void moveStaffSystem(const VSA& arg);
    void moveClef(const VSA& arg);
    void moveKeySignature(const VSA& arg);
    void moveTimeSignature(const VSA& arg);
    void moveNote(const VSA& arg);
    void moveRest(const VSA& arg);
    void moveBarcheck(const VSA& arg);
    void moveSynchroMark(const VSA& arg);

    void ChangeClef(const VSA& arg);
    void changeKeySignature(const VSA& arg);
    void changeTimeSignature(const VSA& arg);
    void changeNoteValue(const VSA& arg);
    void changeRestValue(const VSA& arg);
    void changeSynchroMarkId(const VSA& arg);
    void changeSystem(const VSA& arg);

    void eraseSystemObject(const VSA& arg);



    void changeTitle(const VSA& arg);
};

}

#endif // SCOREMODEL_H
