#include "ClefMenu.h"

ClefMenu::ClefMenu(QWidget *parent)
    : CuteMenu(parent)
{
    treble = addAction(tr("Treble clef"));
    bass = addAction(tr("Bass clef"));
    alto = addAction(tr("Alto clef"));
    neutral = addAction(tr("Neutral clef"));
    other = addAction(tr("Other clef"));
}

QAction* ClefMenu::trebleAction() const
{
    return treble;
}

QAction* ClefMenu::bassAction() const
{
    return bass;
}

QAction* ClefMenu::altoAction() const
{
    return alto;
}

QAction* ClefMenu::neutralAction() const
{
    return neutral;
}

QAction* ClefMenu::otherAction() const
{
    return other;
}

