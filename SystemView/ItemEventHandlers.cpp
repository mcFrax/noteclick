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


SceneEventHandlers::SceneEventHandlers()
{
    HANDLER(SystemImageItem) = 0;
}
