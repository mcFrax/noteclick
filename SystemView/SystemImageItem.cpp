#include "SystemImageItem.h"

using namespace SystemView;

SystemImageItem::SystemImageItem(const QPixmap & pixmap, QGraphicsItem *parent) :
    QGraphicsPixmapItem(pixmap, parent)
{
}

SystemScene *SystemImageItem::systemScene()
{
    return dynamic_cast<SystemScene*>(scene());
}
