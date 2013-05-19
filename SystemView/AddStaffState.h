#ifndef ADDSTAFFSTATE_H
#define ADDSTAFFSTATE_H

#include "SystemSceneState.h"
#include "ItemEventHandlers.h"
#include <QGraphicsPolygonItem>

namespace SystemView
{

class SystemScene;

class AddStaffState : public SystemSceneState, public ItemEventHandler
{
    Q_OBJECT

    void onEntry(QEvent * event);
    void onExit(QEvent * event);
    SceneEventHandlers handlers;

    class StaffPartItem : public QGraphicsPolygonItem
    {
        void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    public:
        StaffPartItem(QGraphicsItem* parent = 0);
    };

    StaffPartItem* staffPartItem;

public:
    explicit AddStaffState(QState * parent, SystemScene *scene);

    bool mouseMoveEvent(QGraphicsItem *, QGraphicsSceneMouseEvent *) override;
    bool mousePressEvent(QGraphicsItem *, QGraphicsSceneMouseEvent *) override;
    bool mouseReleaseEvent(QGraphicsItem *, QGraphicsSceneMouseEvent *) override;

signals:
    void staffSystemAdded();
};

}

#endif // ADDSTAFFSTATE_H
