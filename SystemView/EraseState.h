#ifndef ERASESTATE_H
#define ERASESTATE_H

#include "SystemSceneState.h"
#include "ItemEventHandlers.h"

namespace SystemView
{

class EraseState : public SystemSceneState, public ItemEventHandler
{
    Q_OBJECT

    void onEntry(QEvent * event);
    void onExit(QEvent * event);
    SceneEventHandlers handlers;

    virtual bool mouseReleaseEvent(QGraphicsItem * self, QGraphicsSceneMouseEvent *);
public:
    explicit EraseState(QState *parent, SystemScene *scene);
    
signals:
    
public slots:
    
};

}

#endif // ERASESTATE_H
