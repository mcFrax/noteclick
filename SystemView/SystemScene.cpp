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

void SystemScene::addSystemImageItem(const QString &filename)
{
    QPixmap pixmap(filename);

    if (pixmap.isNull()){
        emit error(tr("Nie udało się otworzyć pliku: ")+'"'+filename+'"');
        return;
    }

    SystemImageItem* newSystem = new SystemImageItem(idReg, anyId, pixmap);
    if (!systemImageItems.empty())
        newSystem->setOffset(0, systemImageItems.back()->boundingRect().bottom());
    systemImageItems.push_back(newSystem);
    addItem(newSystem);
}

void SystemScene::setHandlers(const SceneEventHandlers * handlers)
{
    handlersVal = handlers;
}
