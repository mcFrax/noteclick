#include "AddStaffState.h"
#include "SystemScene.h"

using namespace SystemView;

AddStaffState::AddStaffState(QState * parent, SystemScene *scene) :
    SystemSceneState(parent, scene)
{
    handlers.HANDLER(SystemImageItem) = this;
}


void AddStaffState::onEntry(QEvent *)
{
    scene->setHandlers(&handlers);
}

void AddStaffState::onExit(QEvent *)
{
    scene->setHandlers(0);
}


bool AddStaffState::mousePressEvent(QGraphicsItem *, QGraphicsSceneMouseEvent *)
{
    scene->warning(__PRETTY_FUNCTION__);
    return 1;
}
