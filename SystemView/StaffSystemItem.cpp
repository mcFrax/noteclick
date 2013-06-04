#include "StaffSystemItem.h"

#include <QBrush>
#include <QColor>
#include <QPen>
#include <QGraphicsSceneHoverEvent>
#include <QMessageBox>

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


    topLedgerSpace->setBrush(QColor(30,255,30,60));
    topLedgerSpace->setPen(QColor(0,0,0,0));


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
    
    updateHighlight();


    setCorners(7);
}

void StaffSystemItem::updateHighlight()
{

    QPolygonF ledsp;
    ledsp << position().fromStaffCoords(QPointF(0, 1+ledgerSpaceSize));
    ledsp << position().fromStaffCoords(QPointF(1, 1+ledgerSpaceSize));
    ledsp << position().fromStaffCoords(QPointF(1, 1));
    ledsp << position().fromStaffCoords(QPointF(0, 1));
    topLedgerSpace->setPolygon(ledsp);

    ledsp.clear();
    ledsp << position().fromStaffCoords(QPointF(0, 0));
    ledsp << position().fromStaffCoords(QPointF(1, 0));
    ledsp << position().fromStaffCoords(QPointF(1, -ledgerSpaceSize));
    ledsp << position().fromStaffCoords(QPointF(0, -ledgerSpaceSize));
    bottomLedgerSpace->setPolygon(ledsp);

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

void StaffSystemItem::setCorners(int size)
{
    for (int i = 0; i < 4; i++)
    {
        corner[i] = new Corner(this, size, i, 0, 0 , 2*size, 2*size);
        corner[i]->setPos(this->polygon()[i]);
        corner[i]->setParentItem(this);
    }


}
void StaffSystemItem::adjustCorner(int number, int size)
{
    QPolygonF p = polygon();
    p[number].setX(corner[number]->pos().x() + size);
    p[number].setY(corner[number]->pos().y() + size);
    setPolygon(p);

    setPosition(StaffPosition(p[0], p[1], p[2], p[3]));

    updateHighlight();
    update();
}

QVector<QPointF> StaffSystemItem::setPointOrder(QVector<QPointF> vector)
{
    // sprawdzam czy punkty są parami rózne
    int counter =0;
    foreach (QPointF p1, vector)
    {
        foreach (QPointF p2, vector)
        {
            if (p1 == p2)
                counter++;
        }
    }
    if (counter > 4)
    {
        QMessageBox msgBox;
        msgBox.setText("More than 4 points or equal points passed.");
        msgBox.exec();
        return vector; // TODO EXCEPTION
    }
    QPointF top_left;
    QPointF top_right;
    QPointF bot_left;
    QPointF bot_right;

    QPointF st = vector[0];
    QPointF nd = vector[1];

    if (nd.x() < st.x())
    {
        QPointF tmp = nd;
        nd =st;
        st = tmp;
    }

    bool used[4];

    for (int i=0;i<4;i++)
        used[i] = false;

    // left points
    for(int i =2; i < 4; i++)
    {

        if (vector[i].x() < st.x())
        {
            nd = st;
            st = vector[i];
        }
        else if (vector[i].x() < nd.x())
        {
            nd = vector[i];
        }

    }

    if (st.y() == nd.y())
    {
        QMessageBox msgBox;
        msgBox.setText("Brzydki prostokąt! coś nie bedize działać!");
        msgBox.exec();
        return vector;//EXCEPTION
    }
    else if (st.y() < nd.y())
    {
        top_left = st;
        bot_left = nd;
    }
    else
    {
        top_left = nd;
        bot_left = st;
    }

    for (int i = 0; i < 4; i++)
    {
        if (vector[i] == st || vector[i] == nd)
            used[i] = true;
    }
    // right points


    for (int i = 0; i < 4; i++)
    {
        if (!used[i])
        {
            top_right = vector[i];
            used[i] = true;
            break;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        if (!used[i])
        {
            bot_right = vector[i];
            break;
        }
    }

    if (bot_right.y() < top_right.y())
    {
        QPointF tmp = bot_right;
        bot_right = top_right;
        top_right = tmp;
    }

    QVector<QPointF> result;
    result.append(top_left);
    result.append(top_right);
    result.append(bot_right);
    result.append(bot_left);

    return result;
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
