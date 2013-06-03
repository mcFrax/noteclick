#ifndef ADDNOTESTATE_H
#define ADDNOTESTATE_H

#include "SystemSceneState.h"
#include "ItemEventHandlers.h"
#include "StaffCoords.h"

class QAction;

namespace SystemView
{

class AddNoteState : public SystemSceneState, public ItemEventHandler
{
    Q_OBJECT

    void onEntry(QEvent * event);
    void onExit(QEvent * event);
    SceneEventHandlers handlers;
    IdType staffId;
    StaffCoords coords;
public:
    explicit AddNoteState(QState * parent, SystemScene *scene);

    bool mousePressEvent(QGraphicsItem *, QGraphicsSceneMouseEvent *) override;
    bool mouseReleaseEvent(QGraphicsItem *, QGraphicsSceneMouseEvent *) override;
signals:
    void noteAdded();

private slots:
    void actionTriggered(QAction * action);

public slots:

};

}

#endif // ADDNOTESTATE_H
