#ifndef STAFFSYSTEMITEM_H
#define STAFFSYSTEMITEM_H

#include <QGraphicsPolygonItem>
#include "StaffCoords.h"
#include "SystemViewItem.h"
#include "SystemImageItem.h"

namespace SystemView
{

class StaffSystemItem : private QGraphicsPolygonItem, public SystemViewItem
{
    StaffPosition pos;
    //using QGraphicsPolygonItem::setPolygon(const QPolygonF & polygon);
public:
    StaffSystemItem(Reg &reg, IdType id, const StaffPosition &pos, SystemImageItem* parent = 0);

    using QGraphicsPolygonItem::QGraphicsItem;

    const StaffPosition& position() const;
    void setPosition(const StaffPosition& pos);
};

}

#endif // STAFFSYSTEMITEM_H
