#include "EraseState.h"
#include "SystemViewItem.h"

#include "SignalCommunication/UserAction.h"

using namespace SystemView;

EraseState::EraseState(QState *parent, SystemScene *scene) :
    SystemSceneState(parent, scene)
{
    handlers.HANDLER(StaffSystemItem) = this;
    handlers.HANDLER(SystemImageItem) = this;
    handlers.HANDLER(NoteItem) = this;
    handlers.HANDLER(ClefItem) = this;
}


bool EraseState::mouseReleaseEvent(QGraphicsItem *self, QGraphicsSceneMouseEvent *)
{
//    delete self;
    sceneEmitUserAction(UserAction(UserAction::EraseSystemObject, vsa(dynamic_cast<SystemViewItem*>(self)->id())));
}


void EraseState::onEntry(QEvent *event)
{
    scene->setHandlers(&handlers);
}

void EraseState::onExit(QEvent *event)
{
    scene->setHandlers(0);
}
