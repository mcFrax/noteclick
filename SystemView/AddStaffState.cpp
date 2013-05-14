#include "AddStaffState.h"
#include "ItemEventHandlers.h"
#include "SystemScene.h"

using namespace SystemView;

static AddStaffState::EventHandler handler;
static SceneEventHandlers handlers;

AddStaffState::AddStaffState(QState * parent, SystemScene *scene) :
    SystemSceneState(parent, scene)
{
    handlers.HANDLER(SystemImageItem) = &handler;
}


void AddStaffState::onEntry(QEvent *)
{
    scene->setHandlers(&handlers);
}

void AddStaffState::onExit(QEvent *)
{
    scene->setHandlers(0);
}


bool AddStaffState::EventHandler::mousePressEvent(QGraphicsItem *, QGraphicsSceneMouseEvent *)
{
    return 1;
}
