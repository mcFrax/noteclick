#ifndef CLEFMENU_H
#define CLEFMENU_H

#include "CuteMenu.h"
#include "ClefInfo.h"

#include <QAction>

class QMouseEvent;

class ClefMenu : public CuteMenu
{
    Q_OBJECT
public:
    class Action : public QAction
    {
    public:
        Action(const ClefInfo& clefInfo, const QString & text, QObject * parent = 0);
        Action(const ClefInfo& clefInfo, const QIcon & icon, const QString & text, QObject * parent = 0);

        const ClefInfo clefInfo;
    };

private:
    Action* treble;
    Action* bass;
    Action* alto;
    Action* other;
    void mouseReleaseEvent(QMouseEvent * e) override;
public:
    explicit ClefMenu(QWidget *parent = 0);

    Action* trebleAction() const;
    Action* bassAction() const;
    Action* altoAction() const;
    Action* otherAction() const;
signals:
    
public slots:
    
};

#endif // CLEFMENU_H
