#include "CuteMenu.h"

CuteMenu::CuteMenu(QWidget *parent) :
    QMenu(parent)
{
}


void CuteMenu::mouseReleaseEvent(QMouseEvent *e)
{
    deleteLater();
}
