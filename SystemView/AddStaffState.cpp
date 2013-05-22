#include "AddStaffState.h"
#include "SystemScene.h"
#include "SystemImageItem.h"
#include "StaffCoords.h"

#include <cassert>
#include <QGraphicsSceneMouseEvent>

using namespace SystemView;

AddStaffState::AddStaffState(QState * parent, SystemScene *scene) :
    SystemSceneState(parent, scene), staffPartItem(0)
{
    handlers.HANDLER(SystemImageItem) = this;
}


void AddStaffState::onEntry(QEvent *)
{
    scene->setHandlers(&handlers);
}

void AddStaffState::onExit(QEvent *)
{
    scene->setHandlers(0);
    if (staffPartItem) delete staffPartItem;
    staffPartItem = 0;
}


bool AddStaffState::mouseMoveEvent(QGraphicsItem *, QGraphicsSceneMouseEvent * e)
{
    e->accept();
    return 0;
}


bool AddStaffState::mousePressEvent(QGraphicsItem *, QGraphicsSceneMouseEvent * e)
{
    e->accept();
    return 0;
}

bool AddStaffState::mouseReleaseEvent(QGraphicsItem * system, QGraphicsSceneMouseEvent * e)
{
    #warning: dobrze byloby wymyslic jakis ladny odpowiednik asserta, ktory nie wysypywalby calego procesu
    SystemImageItem* sys = dynamic_cast<SystemImageItem*>(system);
    assert(sys);
    if (e->button() != Qt::LeftButton)
        return 1;
    if (!staffPartItem)
        staffPartItem = new StaffPartItem(sys);
    QPolygonF poly = staffPartItem->polygon();
    poly << e->pos();
    switch (staffPartItem->polygon().size())
    {
    case 0:
    case 1:
    case 2:
        staffPartItem->setPolygon(poly);
        break;
    case 3:
        scene->userAction(UserAction(UserAction::CreateStaffSystem,
                vsa(sys->id(), StaffPosition(poly[0], poly[1], poly[2], poly[3]))));
        emit staffSystemAdded();
        delete staffPartItem;
        staffPartItem = 0;
        break;
    default:
        scene->error(tr("Wystapil blad w funkcji ")+__PRETTY_FUNCTION__);
    }
    return 0;
}


AddStaffState::StaffPartItem::StaffPartItem(QGraphicsItem *parent)
    : QGraphicsPolygonItem(parent)
{
}

void AddStaffState::StaffPartItem::mousePressEvent(QGraphicsSceneMouseEvent * e)
{
    e->ignore();
}
