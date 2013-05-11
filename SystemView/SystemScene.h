#ifndef SYSTEMSCENE_H
#define SYSTEMSCENE_H

#include <QGraphicsScene>
#include <QList>
#include <QState>
#include <QStateMachine>

#include "ItemEventHandlers.h"

namespace SystemView
{

class SystemImageItem;

class SystemScene : public QGraphicsScene
{
    Q_OBJECT

public:
    struct MachineStates
    {
        QState *editSystem;
        QState *normalCursor;
        //QState *addStaff;
        //QState *addClef;
        //QState *addNote;
    };

public:
    explicit SystemScene(QObject *parent = 0);

    const MachineStates& states() const;

    const SceneEventHandlers * handlers() const;
    
signals:
    
public slots:

friend class AddStaffState;

private:
    QStateMachine stateMachine;
    MachineStates statesVal;
    const SceneEventHandlers * handlersVal;
    QList<SystemImageItem*> systemImageItems;
    void setHandlers(const SceneEventHandlers * handlers);

    void setupMachine();

};

}

#endif // SYSTEMSCENE_H
