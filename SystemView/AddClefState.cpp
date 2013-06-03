#include "AddClefState.h"

#include "StaffSystemItem.h"
#include "ClefMenu.h"
#include "SystemScene.h"

#include <QtGlobal>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>

using namespace SystemView;

AddClefState::AddClefState(QState * parent, SystemScene *scene)
    : SystemSceneState(parent, scene)
{
    handlers.HANDLER(StaffSystemItem) = this;
}

bool AddClefState::mousePressEvent(QGraphicsItem * staffItem, QGraphicsSceneMouseEvent *e)
{
    StaffSystemItem* staff = static_cast<StaffSystemItem*>(staffItem);
    Q_ASSERT(staff);
    if (e->button() != Qt::LeftButton)
        return 1;
    if (scene->views().size() != 1)
        scene->warning("scene->views().size() != 1");
    ClefMenu* menu = new ClefMenu(scene->views()[0]);
    connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(actionTriggered(QAction*)));
    staffId = staff->id();
    coords = staff->position().toStaffCoords(e->pos());
    menu->popup(e->screenPos());

    e->accept();
    return 0;
}

bool AddClefState::mouseReleaseEvent(QGraphicsItem *, QGraphicsSceneMouseEvent *)
{
    return 1;
}


void AddClefState::onEntry(QEvent *)
{
    scene->setHandlers(&handlers);
}

void AddClefState::onExit(QEvent *)
{
    scene->setHandlers(0);
}


void AddClefState::actionTriggered(QAction * action)
{
    ClefInfo info = static_cast<ClefMenu::Action*>(action)->clefInfo;
    if (!info.isValid()){
        scene->error(tr("Not handled yet"));
    } else {
        scene->userAction(UserAction(UserAction::CreateClef, vsa(staffId, coords, info)));
        emit clefAdded();
    }
}
