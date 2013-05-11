#ifndef SYSTEMIMAGEITEM_H
#define SYSTEMIMAGEITEM_H

#include <QGraphicsPixmapItem>

#include "ItemEventHandlers.h"
#include "SystemScene.h"

namespace SystemView
{

/*!Class representing single system background image.
 *
 * System can have many SystemImages, e.g. with different instruments.
 */
class SystemImageItem : public QGraphicsPixmapItem
{
    USE_EVENT_HANDLERS(HANDLER(SystemImageItem), QGraphicsPixmapItem)
public:
    explicit SystemImageItem(const QPixmap & pixmap, QGraphicsItem *parent = 0);

protected:
    SystemScene * systemScene();
};

}

#endif // SYSTEMIMAGEITEM_H
