#ifndef CLEFITEM_H
#define CLEFITEM_H

#include <QGraphicsPathItem>

#include "ItemEventHandlers.h"
#include "SystemScene.h"
#include "SystemViewItem.h"
#include "ClefInfo.h"
#include "StaffCoords.h"

namespace SystemView
{

class StaffSystemItem;

class ClefItem : private QGraphicsPathItem, public SystemViewItem
{
    USE_EVENT_HANDLERS(HANDLER(ClefItem), QGraphicsPathItem)
    ClefInfo info;
    StaffCoords coords;
public:
    ClefItem(Reg &reg, IdType id, const StaffCoords &coords, const ClefInfo& clefInfo, StaffSystemItem* parent);

    using QGraphicsPathItem::QGraphicsItem;

    ClefInfo clefInfo() const;
    StaffCoords staffCoords() const;

protected:
    SystemScene * systemScene();
};

}

#endif // CLEFITEM_H
