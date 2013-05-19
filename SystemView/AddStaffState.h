#ifndef ADDSTAFFSTATE_H
#define ADDSTAFFSTATE_H

#include "SystemSceneState.h"
#include "ItemEventHandlers.h"

namespace SystemView
{

class SystemScene;

class AddStaffState : public SystemSceneState, public ItemEventHandler
{
    Q_OBJECT

    void onEntry(QEvent * event);
    void onExit(QEvent * event);
    SceneEventHandlers handlers;
public:
    explicit AddStaffState(QState * parent, SystemScene *scene);

    bool mousePressEvent(QGraphicsItem *, QGraphicsSceneMouseEvent *);
};

}

#endif // ADDSTAFFSTATE_H
