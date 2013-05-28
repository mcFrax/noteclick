#ifndef NOTEMENU_H
#define NOTEMENU_H

#include "CuteMenu.h"
#include "NoteValue.h"

class NoteMenu : public CuteMenu
{
    Q_OBJECT
public:
    class Action : public QAction
    {
    public:
        Action(const NoteValue& noteValue, const QString & text, QObject * parent = 0);
        Action(const NoteValue& noteValue, const QIcon & icon, const QString & text, QObject * parent = 0);

        const NoteValue noteValue;
    };

private:
    int actcount;
    Action* longa;
    Action* breve;
    Action* semibreve;
    Action* minim;
    Action* crotchet;
    Action* quaver;
    Action* semiquaver;
    Action* demisemiquaver;
    Action* hemidemisemiquaver;
    Action* quasihemidemisemiquaver;
    void mouseReleaseEvent(QMouseEvent * e) override;
public:
    explicit NoteMenu(QWidget *parent = 0);
    void popup(const QPoint & p, QAction * atAction = 0);
signals:
    
public slots:
    
};

#endif // NOTEMENU_H
