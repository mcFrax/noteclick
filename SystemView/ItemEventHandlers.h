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
};

class SceneEventHandlers
{
public:
    SceneEventHandlers();
    ItemEventHandler* HANDLER(SystemImageItem);
    //ItemEventHandler* staffItemHandler;
    //ItemEventHandler* clefItemHandler;
    //ItemEventHandler* noteItemHandler;
};

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
    
#define USE_EVENT_HANDLERS(HANDLER_NAME, PARENT_CLASS)                                                \
    USE_EVENT_HANDLER(mousePressEvent, QGraphicsSceneMouseEvent, HANDLER_NAME, PARENT_CLASS) \
    USE_EVENT_HANDLER(mouseMoveEvent, QGraphicsSceneMouseEvent, HANDLER_NAME, PARENT_CLASS)  \
    //=============================================================================================//

#endif // ITEMEVENTHANDLERS_H
