#include "EraseState.h"
#include <QGraphicsItem>
#include <QtGlobal>
#include <QGraphicsSceneMouseEvent>
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


bool EraseState::mousePressEvent(QGraphicsItem *, QGraphicsSceneMouseEvent *e)
{
    e->accept();
    return 0;
}

bool EraseState::mouseReleaseEvent(QGraphicsItem *self, QGraphicsSceneMouseEvent *)
{
//    delete self;
    SystemViewItem* svi = dynamic_cast<SystemViewItem*>(self);
    if (svi)
        sceneEmitUserAction(UserAction(UserAction::EraseSystemObject, vsa(svi->id())));
    else
        qDebug("No kurcze.");
    return 0;
}


void EraseState::onEntry(QEvent *)
{
    scene->setHandlers(&handlers);
}

void EraseState::onExit(QEvent *)
{
    scene->setHandlers(0);
}
