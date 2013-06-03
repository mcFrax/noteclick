#include "ItemEventHandlers.h"

using namespace SystemView;

bool ItemEventHandler::mousePressEvent(QGraphicsItem *, QGraphicsSceneMouseEvent *)
{
    return 1;
}

bool ItemEventHandler::mouseMoveEvent(QGraphicsItem *, QGraphicsSceneMouseEvent *)
{
    return 1;
}

bool ItemEventHandler::mouseReleaseEvent(QGraphicsItem *, QGraphicsSceneMouseEvent *)
{
    return 1;
}

bool IgnoringItemEventHandler::mousePressEvent(QGraphicsItem *, QGraphicsSceneMouseEvent *)
{
    return 0;
}

bool IgnoringItemEventHandler::mouseMoveEvent(QGraphicsItem *, QGraphicsSceneMouseEvent *)
{
    return 0;
}

bool IgnoringItemEventHandler::mouseReleaseEvent(QGraphicsItem *, QGraphicsSceneMouseEvent *)
{
    return 0;
}

ItemEventHandler* SystemView::defaultItemEventHandler()
{
    static ItemEventHandler instance;
    return &instance;
}

ItemEventHandler* SystemView::ignoringItemEventHandler()
{
    static IgnoringItemEventHandler instance;
    return &instance;
}


SceneEventHandlers::SceneEventHandlers()
{
    HANDLER(SystemImageItem) = 0;
    HANDLER(StaffSystemItem) = 0;
    HANDLER(ClefItem) = 0;
}


IgnoringSceneEventHandlers::IgnoringSceneEventHandlers()
{
    HANDLER(SystemImageItem) = ignoringItemEventHandler();
    HANDLER(StaffSystemItem) = ignoringItemEventHandler();
    HANDLER(ClefItem) = ignoringItemEventHandler();
}
