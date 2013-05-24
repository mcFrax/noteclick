#ifndef ITEMEVENTHANDLERS_H
#define ITEMEVENTHANDLERS_H

class QGraphicsItem;
class QGraphicsSceneMouseEvent;
class QKeyEvent;

#define HANDLER(CLASS_NAME) CLASS_NAME##Handler

namespace SystemView
{

class ItemEventHandler
{
public:
    virtual bool mousePressEvent(QGraphicsItem * self, QGraphicsSceneMouseEvent *);
    virtual bool mouseMoveEvent(QGraphicsItem * self, QGraphicsSceneMouseEvent *);
    virtual bool mouseReleaseEvent(QGraphicsItem * self, QGraphicsSceneMouseEvent *);
};

class IgnoringItemEventHandler : public ItemEventHandler
{
public:
    bool mousePressEvent(QGraphicsItem * self, QGraphicsSceneMouseEvent *) override;
    bool mouseMoveEvent(QGraphicsItem * self, QGraphicsSceneMouseEvent *) override;
    bool mouseReleaseEvent(QGraphicsItem * self, QGraphicsSceneMouseEvent *) override;
};

struct SceneEventHandlers
{
    SceneEventHandlers();
    ItemEventHandler* HANDLER(SystemImageItem);
    ItemEventHandler* HANDLER(StaffSystemItem);
    ItemEventHandler* HANDLER(ClefItem);
    //ItemEventHandler* noteItemHandler;
};

struct IgnoringSceneEventHandlers : public SceneEventHandlers
{
    IgnoringSceneEventHandlers();
};

ItemEventHandler* defaultItemEventHandler();
ItemEventHandler* ignoringItemEventHandler();

}


#define USE_EVENT_HANDLER(METHOD_NAME, ARG_TYPE, HANDLER_NAME, PARENT_CLASS) \
    void METHOD_NAME(ARG_TYPE * event)                                       \
    {                                                                        \
        if (!systemScene()->handlers()                                       \
                || !systemScene()->handlers()->HANDLER_NAME                  \
                || systemScene()                                             \
                   ->handlers()                                              \
                   ->HANDLER_NAME                                            \
                   ->METHOD_NAME(this, event)){                              \
            PARENT_CLASS::METHOD_NAME(event);                                \
        }                                                                    \
    }                                                                        \
    //======================================================================//
    
#define USE_EVENT_HANDLERS(HANDLER_NAME, PARENT_CLASS)                                       \
    USE_EVENT_HANDLER(mousePressEvent, QGraphicsSceneMouseEvent, HANDLER_NAME, PARENT_CLASS) \
    USE_EVENT_HANDLER(mouseMoveEvent, QGraphicsSceneMouseEvent, HANDLER_NAME, PARENT_CLASS)  \
    USE_EVENT_HANDLER(mouseReleaseEvent, QGraphicsSceneMouseEvent, HANDLER_NAME, PARENT_CLASS)  \
    //======================================================================================//

#endif // ITEMEVENTHANDLERS_H
