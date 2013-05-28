#include "MusicItem.h"

using namespace SystemView;

MusicItem::MusicItem(QGraphicsItem *parent) :
    QGraphicsPixmapItem()
{
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    currentState = -1;
    generateStates();
}

QPixmap MusicItem::changeColor(const QPixmap &pixmap, QColor c)
{
    QImage image = pixmap.toImage();
    QRgb old;
    int width = pixmap.width();
    int height = pixmap.height();
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            old = image.pixel(i, j);
            if (qAlpha(old) == 255)
                image.setPixel(i, j, c.rgb());
        }
    }

    return pixmap.fromImage(image);
}

void MusicItem::addState(int number, QPixmap &pixmap)
{
    states[number] = pixmap;
}

void MusicItem::setState(int number)
{
    currentState = number;
    setPixmap(states[number]);
}

int MusicItem::getState()
{
   return currentState;
}

void MusicItem::generateStates()
{

}
