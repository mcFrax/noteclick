#ifndef ADDSTAFFSTATE_H
#define ADDSTAFFSTATE_H

#include "SystemSceneState.h"

namespace SystemView
{

class SystemScene;

class AddStaffState : public SystemSceneState
{
    Q_OBJECT

    void onEntry(QEvent * event);
    void onExit(QEvent * event);
public:
    explicit AddStaffState(QState * parent, SystemScene *scene);

    class EventHandler : public ItemEventHandler
    {
        bool mousePressEvent(QGraphicsItem *, QGraphicsSceneMouseEvent *);
    };
};

}

#endif // ADDSTAFFSTATE_H
