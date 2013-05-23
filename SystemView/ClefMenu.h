#ifndef CLEFMENU_H
#define CLEFMENU_H

#include "CuteMenu.h"
#include <QAction>

class ClefMenu : public CuteMenu
{
    Q_OBJECT
    QAction* treble;
    QAction* bass;
    QAction* alto;
    QAction* neutral;
    QAction* other;
public:
    explicit ClefMenu(QWidget *parent = 0);

    QAction* trebleAction() const;
    QAction* bassAction() const;
    QAction* altoAction() const;
    QAction* neutralAction() const;
    QAction* otherAction() const;
signals:
    
public slots:
    
};

#endif // CLEFMENU_H
