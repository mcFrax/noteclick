#ifndef STAFFSYSTEMITEM_H
#define STAFFSYSTEMITEM_H

#include <QGraphicsPolygonItem>
#include "StaffCoords.h"
#include "SystemScene.h"
#include "SystemViewItem.h"
#include "SystemImageItem.h"

class QGraphicsSceneHoverEvent;

namespace SystemView
{

class StaffSystemItem : private QGraphicsPolygonItem, public SystemViewItem
{
    USE_EVENT_HANDLERS(HANDLER(StaffSystemItem), QGraphicsPolygonItem)
    StaffPosition pos;
    //using QGraphicsPolygonItem::setPolygon(const QPolygonF & polygon);
    class LedgerSpaceItem;
    friend class StaffSystemItem::LedgerSpaceItem;
    LedgerSpaceItem* topLedgerSpace;
    LedgerSpaceItem* bottomLedgerSpace;
    QGraphicsPolygonItem* lineHighlight;
    QGraphicsPolygonItem* spaceHighlight;
    void hoverMoveEvent(QGraphicsSceneHoverEvent * event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
public:
    StaffSystemItem(Reg &reg, IdType id, const StaffPosition &pos, SystemImageItem* parent);

    using QGraphicsPolygonItem::QGraphicsItem;

    const StaffPosition& position() const;
    void setPosition(const StaffPosition& pos);

protected:
    SystemScene * systemScene();
};

}

#endif // STAFFSYSTEMITEM_H
