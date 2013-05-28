#ifndef MUSICITEM_H
#define MUSICITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>

class MusicItem : public QGraphicsPixmapItem
{
    //Q_OBJECT
public:
    explicit MusicItem(QGraphicsItem *parent = 0);


    static QPixmap changeColor(QPixmap &pixmap, QColor c);

signals:
    
public slots:

protected:
    virtual void generateStates();

    void addState(int number, QPixmap &pixmap);
    void setState(int number);
    int getState();

    int currentState;
    QMap<int, QPixmap> states;

};

#endif // MUSICITEM_H
