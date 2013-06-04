#ifndef STAFFSYSTEMITEM_H
#define STAFFSYSTEMITEM_H

#include <QGraphicsPolygonItem>
#include "StaffCoords.h"
#include "SystemScene.h"
#include "SystemViewItem.h"
#include "SystemImageItem.h"
#include <QMessageBox>

class QGraphicsSceneHoverEvent;

namespace SystemView
{

class Corner;

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

    //corners - wojtek
    void adjustCorner(int number, int size);
    void setCorners(int size);

    static QVector<QPointF> setPointOrder(QVector<QPointF> vector);
protected:
    SystemScene * systemScene();

    // corners - wojtek
    const int left_top = 0;
    const int right_top = 1;
    const int right_bottom = 2;
    const int left_bottom = 3;

    Corner *corner[4];


};



class Corner : public QGraphicsRectItem
{
public:
    Corner(StaffSystemItem* staff, int size, int number, qreal x, qreal y, qreal w, qreal h, QGraphicsItem* parent = 0):QGraphicsRectItem(x, y, w, h, parent)
    {
        this->staff = staff;
        this->number = number;
        this->size = size;
        setPen(QColor(0,200,0,255));
        setBrush(QColor(0,0,0,255));
        setFlag(ItemSendsScenePositionChanges);
        setFlag(ItemIsMovable);
        setFlag(ItemIsSelectable);
    }

protected:

    int number;
    int size;
    StaffSystemItem* staff;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value)
    {


        switch (change) {
        case ItemPositionHasChanged:
            staff->adjustCorner(number, size);
          break;
        default:
            break;
        };

        return QGraphicsItem::itemChange(change, value);
    }

};

}

#endif // STAFFSYSTEMITEM_H
