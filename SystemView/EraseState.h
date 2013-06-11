#ifndef ERASESTATE_H
#define ERASESTATE_H

#include "SystemSceneState.h"
#include "ItemEventHandler.h"

using namespace SystemView;

class EraseState : public SystemSceneState, public ItemEventHandler
{
    Q_OBJECT
    virtual bool mouseReleaseEvent(QGraphicsItem * self, QGraphicsSceneMouseEvent *);
public:
    explicit EraseState(QState *parent = 0);
    
signals:
    
public slots:
    
};

#endif // ERASESTATE_H
