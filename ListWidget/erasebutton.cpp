#include "erasebutton.h"

using namespace StructureView;

EraseButton::EraseButton(QWidget *parent) :
    QPushButton(parent)
{
    setFixedHeight(23);
    setFixedWidth(23);
    setText("x");
    setFocusPolicy(Qt::NoFocus);
    setStyleSheet("QPushButton {"
                  "border: 1px solid black;"
                  "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                    "stop: 0 #FF7373, stop: 1 #A60000);"
                  "border-radius: 4px;"
                  "padding: 4px;"
                  "font-weight: bold;"
                  "}"
                  "QPushButton:pressed{"
                  "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                      "stop: 0 #A60000, stop: 1 #FF7373);"
                  "border-radius: 4px;"
                                  "}");
}
