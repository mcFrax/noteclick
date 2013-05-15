#ifndef SYSTEMSCENE_H
#define SYSTEMSCENE_H

#include <QGraphicsScene>
#include <QList>
#include <QStateMachine>

class QState;
class QString;

#include "ItemEventHandlers.h"
#include "IdRegisteredClass.h"
#include "SignalCommunication/UserAction.h"
#include "SignalCommunication/ScoreChange.h"

namespace SystemView
{

class SystemImageItem;
class SystemSceneState;

class SystemScene : public QGraphicsScene
{
    Q_OBJECT

public:
    struct MachineStates
    {
        QState *editSystem;
        QState *normalCursor;
        QState *addStaff;
        //QState *addClef;
        //QState *addNote;
    };

public:
    explicit SystemScene(QObject *parent = 0);

    const MachineStates& states() const;

    const SceneEventHandlers * handlers() const;
    
signals:
    void error(QString errorMessage);
    void warning(QString what);
    void notice(QString what);

    void userAction(UserAction);
    
public slots:
    void scoreChange(ScoreChange change);

friend class SystemSceneState;
friend class AddStaffState;

private:
    Reg idReg;
    QStateMachine stateMachine;
    MachineStates statesVal;
    const SceneEventHandlers * handlersVal;
    QList<SystemImageItem*> systemImageItems;
    void setHandlers(const SceneEventHandlers * handlers);

    void setupMachine();

};

}

#endif // SYSTEMSCENE_H
