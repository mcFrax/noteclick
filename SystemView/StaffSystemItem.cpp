#include "StaffSystemItem.h"

#include <QBrush>
#include <QColor>
#include <QPen>
#include <QMessageBox>

using namespace SystemView;

StaffSystemItem::StaffSystemItem(Reg &reg, IdType id, const StaffPosition &pos, SystemImageItem* parent)
    : QGraphicsPolygonItem(pos.toQPolygonF(), parent), SystemViewItem(reg, id), pos(pos)
{
    setBrush(QColor(0,255,0,80));
    setPen(QColor(0,255,0,200));

    setCorners(7);

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
