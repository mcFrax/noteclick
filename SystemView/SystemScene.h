#ifndef SYSTEMSCENE_H
#define SYSTEMSCENE_H

#include <QGraphicsScene>
#include <QList>
#include <QState>
#include <QStateMachine>

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

    const MachineStates& states();
    
signals:
    
public slots:

private:
    QStateMachine stateMachine;
    MachineStates statesVal;
    QList<SystemImageItem*> systemImageItems;

    void setupMachine();

};

}

#endif // SYSTEMSCENE_H
