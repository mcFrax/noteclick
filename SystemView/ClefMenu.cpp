#include "ClefMenu.h"

#include <QMouseEvent>
#include <QtGlobal>

ClefMenu::ClefMenu(QWidget *parent)
    : CuteMenu(parent)
{
    treble = new Action(ClefInfo(ClefInfo::GClef, 2), tr("Treble clef"), this);
    bass = new Action(ClefInfo(ClefInfo::FClef, 6), tr("Bass clef"), this);
    alto = new Action(ClefInfo(ClefInfo::CClef, 4), tr("Alto clef"), this);
    other = new Action(ClefInfo(), tr("Other clef"), this);
    addAction(treble);
    addAction(bass);
    addAction(alto);
    addAction(other);
}


ClefMenu::Action::Action(const ClefInfo &clefInfo, const QString &text, QObject *parent)
    : QAction(text, parent), clefInfo(clefInfo)
{
}

ClefMenu::Action::Action(const ClefInfo &clefInfo, const QIcon &icon, const QString &text, QObject *parent)
    : QAction(icon, text, parent), clefInfo(clefInfo)
{
}

void ClefMenu::mouseReleaseEvent(QMouseEvent *e)
{
    QMenu::mouseReleaseEvent(e);
    deleteLater();
}

