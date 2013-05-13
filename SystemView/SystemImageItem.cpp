#include "SystemImageItem.h"

using namespace SystemView;

SystemImageItem::SystemImageItem(Reg &reg, IdType id, const QPixmap & pixmap, QGraphicsItem *parent) :
    QGraphicsPixmapItem(pixmap, parent), SystemViewItem(reg, id)
{
}

SystemScene *SystemImageItem::systemScene()
{
    return dynamic_cast<SystemScene*>(scene());
}
