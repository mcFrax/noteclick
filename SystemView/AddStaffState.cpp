#include "AddStaffState.h"
#include "ItemEventHandlers.h"
#include "SystemScene.h"

using namespace SystemView;

class EventHandler : public ItemEventHandler
{
    bool mousePressEvent(QGraphicsItem *, QGraphicsSceneMouseEvent *) { throw 1; return 0; }
};

static EventHandler handler;
static SceneEventHandlers handlers;

AddStaffState::AddStaffState(QState * parent, SystemScene *scene) :
    QState(parent), scene(scene)
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
