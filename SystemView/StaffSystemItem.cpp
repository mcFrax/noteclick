#include "StaffSystemItem.h"

#include <QBrush>
#include <QColor>
#include <QPen>
#include <QGraphicsSceneHoverEvent>

using namespace SystemView;

class StaffSystemItem::LedgerSpaceItem : public QGraphicsPolygonItem
{
    StaffSystemItem* staff;
public:
    LedgerSpaceItem(StaffSystemItem*parent) : QGraphicsPolygonItem(parent), staff(parent) {}
    void hoverMoveEvent(QGraphicsSceneHoverEvent * event) { staff->hoverMoveEvent(event); }
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event) { staff->hoverEnterEvent(event); }
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event) { staff->hoverLeaveEvent(event); }
    void mousePressEvent(QGraphicsSceneMouseEvent *event) { event->ignore(); }
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) { event->ignore(); }
};

static const double ledgerSpaceSize = 0.5;

StaffSystemItem::StaffSystemItem(Reg &reg, IdType id, const StaffPosition &pos, SystemImageItem* parent)
    : QGraphicsPolygonItem(pos.toQPolygonF(), parent), SystemViewItem(reg, id), pos(pos)
{
    setBrush(QColor(0,255,0,80));
    setPen(QColor(0,255,0,200));
    setAcceptHoverEvents(1);
    topLedgerSpace = new LedgerSpaceItem(this);
    bottomLedgerSpace = new LedgerSpaceItem(this);
    topLedgerSpace->setAcceptHoverEvents(1);
    bottomLedgerSpace->setAcceptHoverEvents(1);

    QPolygonF ledsp;
    ledsp << position().fromStaffCoords(QPointF(0, 1+ledgerSpaceSize));
    ledsp << position().fromStaffCoords(QPointF(1, 1+ledgerSpaceSize));
    ledsp << position().fromStaffCoords(QPointF(1, 1));
    ledsp << position().fromStaffCoords(QPointF(0, 1));
    topLedgerSpace->setPolygon(ledsp);
    topLedgerSpace->setBrush(QColor(30,255,30,60));
    topLedgerSpace->setPen(QColor(0,0,0,0));

    ledsp.clear();
    ledsp << position().fromStaffCoords(QPointF(0, 0));
    ledsp << position().fromStaffCoords(QPointF(1, 0));
    ledsp << position().fromStaffCoords(QPointF(1, -ledgerSpaceSize));
    ledsp << position().fromStaffCoords(QPointF(0, -ledgerSpaceSize));
    bottomLedgerSpace->setPolygon(ledsp);
    bottomLedgerSpace->setBrush(QColor(50,255,50,60));
    bottomLedgerSpace->setPen(QColor(0,0,0,0));

    lineHighlight = new QGraphicsPolygonItem(this);
    spaceHighlight = new QGraphicsPolygonItem(this);
    lineHighlight->setVisible(0);
    spaceHighlight->setVisible(0);
    lineHighlight->setZValue(-1); //mają być z tyłu, żeby myszy nie zabierać
    spaceHighlight->setZValue(-1);

    lineHighlight->setBrush(QColor(0,255,0,200));
    lineHighlight->setPen(QColor(0,255,0,80));

    spaceHighlight->setBrush(QColor(0,255,0,80));
    spaceHighlight->setPen(QColor(0,255,0,200));
}

void StaffSystemItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    static const float lineHighlightWidth = 0.1; //w StaffCoords
    static const float spaceHighlightWidth = 0.125;
    static const float lhw = lineHighlightWidth/2;
    static const float shw = spaceHighlightWidth/2;
    int pos = position().toStaffCoords(event->pos()).positionOnStaff();
//    qDebug("%f, %i", position().toStaffCoords(event->pos()).y(), pos);
    if (pos%2 == 0){
        //podświetlamy linię
        lineHighlight->setVisible(1);
        spaceHighlight->setVisible(0);
        QPolygonF highlight;
        highlight << position().fromStaffCoords(QPointF(0, pos/8.0-lhw));
        highlight << position().fromStaffCoords(QPointF(1, pos/8.0-lhw));
        highlight << position().fromStaffCoords(QPointF(1, pos/8.0+lhw));
        highlight << position().fromStaffCoords(QPointF(0, pos/8.0+lhw));
        lineHighlight->setPolygon(highlight);
    } else {
        //podświetlamy pole
        lineHighlight->setVisible(0);
        spaceHighlight->setVisible(1);
        QPolygonF highlight;
        highlight << position().fromStaffCoords(QPointF(0, pos/8.0-shw));
        highlight << position().fromStaffCoords(QPointF(1, pos/8.0-shw));
        highlight << position().fromStaffCoords(QPointF(1, pos/8.0+shw));
        highlight << position().fromStaffCoords(QPointF(0, pos/8.0+shw));
        spaceHighlight->setPolygon(highlight);
    }
}

void StaffSystemItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    hoverMoveEvent(event);
}

void StaffSystemItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    lineHighlight->setVisible(0);
    spaceHighlight->setVisible(0);
}

const StaffPosition &StaffSystemItem::position() const
{
    return pos;
}

void StaffSystemItem::setPosition(const StaffPosition &pos)
{
    this->pos = pos;
}

SystemScene *StaffSystemItem::systemScene()
{
    return dynamic_cast<SystemScene*>(scene());
}
