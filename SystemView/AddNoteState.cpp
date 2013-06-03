#include "AddNoteState.h"

#include "StaffSystemItem.h"
#include "SystemScene.h"
#include "NoteMenu.h"

#include <QtGlobal>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>

using namespace SystemView;

AddNoteState::AddNoteState(QState * parent, SystemScene *scene)
    : SystemSceneState(parent, scene)
{
    handlers.HANDLER(StaffSystemItem) = this;
}

bool AddNoteState::mousePressEvent(QGraphicsItem * staffItem, QGraphicsSceneMouseEvent *e)
{
    StaffSystemItem* staff = static_cast<StaffSystemItem*>(staffItem);
    Q_ASSERT(staff);
    if (e->button() != Qt::LeftButton)
        return 1;
    if (scene->views().size() != 1)
        scene->warning("scene->views().size() != 1");
    NoteMenu* menu = new NoteMenu(scene->views()[0]);
    connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(actionTriggered(QAction*)));
    staffId = staff->id();
    coords = staff->position().toStaffCoords(e->pos());
    menu->popup(e->screenPos());

    e->accept();
    return 0;
}

bool AddNoteState::mouseReleaseEvent(QGraphicsItem *, QGraphicsSceneMouseEvent *)
{
    return 1;
}

void AddNoteState::onEntry(QEvent *)
{
    scene->setHandlers(&handlers);
}

void AddNoteState::onExit(QEvent *)
{
    scene->setHandlers(0);
}


void AddNoteState::actionTriggered(QAction * action)
{
    NoteValue value = static_cast<NoteMenu::Action*>(action)->noteValue;
    if (scene->currentVoice() == noneId){
        scene->error(tr("Brak biezacego glosu"));
    } else {
        scene->userAction(UserAction(UserAction::CreateNote, vsa(staffId, coords, scene->currentVoice(), value)));
        emit noteAdded();
    }
}
