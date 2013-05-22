#include "StaffSystemItem.h"

#include <QBrush>
#include <QColor>
#include <QPen>

using namespace SystemView;

StaffSystemItem::StaffSystemItem(Reg &reg, IdType id, const StaffPosition &pos, SystemImageItem* parent)
    : QGraphicsPolygonItem(pos.toQPolygonF(), parent), SystemViewItem(reg, id), pos(pos)
{
    setBrush(QColor(0,255,0,80));
    setPen(QColor(0,255,0,200));
}

const StaffPosition &StaffSystemItem::position() const
{
    return pos;
}

void StaffSystemItem::setPosition(const StaffPosition &pos)
{
    this->pos = pos;
}
