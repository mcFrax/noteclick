#ifndef ADDCLEFSTATE_H
#define ADDCLEFSTATE_H

#include "SystemSceneState.h"
#include "ItemEventHandlers.h"
#include "StaffCoords.h"

class QAction;

namespace SystemView
{

class AddClefState : public SystemSceneState, public ItemEventHandler
{
    Q_OBJECT

    void onEntry(QEvent * event);
    void onExit(QEvent * event);
    SceneEventHandlers handlers;
    IdType staffId;
    StaffCoords coords;
public:
    explicit AddClefState(QState * parent, SystemScene *scene);

    bool mousePressEvent(QGraphicsItem *, QGraphicsSceneMouseEvent *) override;
    bool mouseReleaseEvent(QGraphicsItem *, QGraphicsSceneMouseEvent *) override;
signals:
    void clefAdded();

private slots:
    void actionTriggered(QAction*action);

public slots:
    
};

}

#endif // ADDCLEFSTATE_H
