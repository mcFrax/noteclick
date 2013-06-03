#ifndef CUTEMENU_H
#define CUTEMENU_H

#include <QMenu>

class CuteMenu : public QMenu
{
    Q_OBJECT
protected:
    void mouseReleaseEvent(QMouseEvent * e);
public:
    explicit CuteMenu(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // CUTEMENU_H
