#include "NoteMenu.h"

NoteMenu::NoteMenu(QWidget *parent) :
    CuteMenu(parent)
{
    actcount = 0;
#define ADD_NEW_ACTION_TO_THIS_NOTE_MENU(var, value, string) do {var = new Action(NoteValue(value), tr( #string ), this); addAction(var); ++actcount;}while(0)
    ADD_NEW_ACTION_TO_THIS_NOTE_MENU(longa, 4, Longa);
    ADD_NEW_ACTION_TO_THIS_NOTE_MENU(breve, 2, Breve);
    ADD_NEW_ACTION_TO_THIS_NOTE_MENU(semibreve, 1, Semibreve);
    ADD_NEW_ACTION_TO_THIS_NOTE_MENU(minim, 0.5, Minim);
    ADD_NEW_ACTION_TO_THIS_NOTE_MENU(crotchet, 0.25, Crotchet);
    ADD_NEW_ACTION_TO_THIS_NOTE_MENU(quaver, 0.125, Quaver);
    ADD_NEW_ACTION_TO_THIS_NOTE_MENU(semiquaver, 0.0625, Semiquaver);
    ADD_NEW_ACTION_TO_THIS_NOTE_MENU(demisemiquaver, 0.03125, Demisemiquaver);
    ADD_NEW_ACTION_TO_THIS_NOTE_MENU(hemidemisemiquaver, 0.015625, Hemidemisemiquaver);
    ADD_NEW_ACTION_TO_THIS_NOTE_MENU(quasihemidemisemiquaver, 0.0078125, Quasihemidemisemiquaver);
#undef ADD_NEW_ACTION_TO_THIS_NOTE_MENU
}


NoteMenu::Action::Action(const NoteValue &noteValue, const QString &text, QObject *parent)
    : QAction(text, parent), noteValue(noteValue)
{
}

NoteMenu::Action::Action(const NoteValue &noteValue, const QIcon &icon, const QString &text, QObject *parent)
    : QAction(icon, text, parent), noteValue(noteValue)
{
}

void NoteMenu::mouseReleaseEvent(QMouseEvent *e)
{
    QMenu::mouseReleaseEvent(e);
    deleteLater();
}

void NoteMenu::popup(const QPoint & p, QAction * atAction)
{
    QSize h = sizeHint();
    QMenu::popup(p - QPoint(h.width()/2, h.height()/actcount/2), atAction);
}
