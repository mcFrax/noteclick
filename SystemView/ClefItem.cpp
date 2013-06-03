#include "ClefItem.h"

#include <QPainterPath>
#include <QtGlobal>
#include <cassert>

#include "StaffSystemItem.h"

using namespace SystemView;

static const QPainterPath& painterPath(ClefInfo::ClefType clefType);

ClefItem::ClefItem(Reg &reg, IdType id, const StaffCoords &coords, const ClefInfo& info, StaffSystemItem* parent)
    : QGraphicsPathItem(painterPath(info.type()), parent), SystemViewItem(reg, id), info(info), coords(coords)
{
    setPos(parent->position().fromStaffCoords(coords));
}

ClefInfo ClefItem::clefInfo() const
{
    return info;
}

StaffCoords ClefItem::staffCoords() const
{
    return coords;
}

SystemScene *ClefItem::systemScene()
{
    return dynamic_cast<SystemScene*>(scene());
}

static QPainterPath getGClefPath()
{
    QPainterPath path;
    float a = 8;
    path.moveTo(0, 0);
    path.arcTo(-a, -a/2, a, a, 0*360, -0.5*360);
    path.arcTo(-a, -a, 2*a, 2*a, 0.5*360, -0.5*360);
    path.arcTo(-1.5*a, -1.5*a, 2.5*a, 2.5*a, 0*360, -0.7*360);
    QPointF endp = path.pointAtPercent(1);
    path.quadTo(endp+QPointF(1.5*a, -1.5*a), endp+QPointF(0.5*a, -3*a));
    endp = path.pointAtPercent(1);
    path.quadTo(endp+QPointF(-0.6*a, 3*a), endp+QPointF(0, 6*a));
    return path;
}

static QPainterPath getFClefPath()
{
    QPainterPath path;
    float a = 5;
    path.moveTo(-2*a, -a);
    path.quadTo(0, -1.5*a, -2*a, 2*a);
    path.moveTo(0, -a);
    path.addEllipse(0, -a, 1, 1);
    path.moveTo(0, a);
    path.addEllipse(0, a, 1, 1);
    return path;
}

static QPainterPath getCClefPath()
{
    QPainterPath path;
    float a = 6;
    path.moveTo(-a, -3*a);
    path.lineTo(-a, 3*a);
    path.moveTo(-a, 0);
    path.lineTo(a, -3*a);
    path.moveTo(-a, 0);
    path.lineTo(a, 3*a);
    return path;
}

static const QPainterPath gClefPath = getGClefPath();
static const QPainterPath fClefPath = getFClefPath();
static const QPainterPath cClefPath = getCClefPath();

const QPainterPath &painterPath(ClefInfo::ClefType clefType)
{
    switch (clefType)
    {
    case ClefInfo::GClef:
        return gClefPath;
    case ClefInfo::FClef:
        return fClefPath;
    case ClefInfo::CClef:
        return cClefPath;
    case ClefInfo::Invalid:
    default:
        Q_ASSERT(false);
    }
    assert(false); //bo __builtin_unreachable(); uznałem za nieprzenośne.
}
