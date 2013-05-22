#include "staff.h"

#include "voicewidget.h"

Staff::Staff(QString name, Score *sc, QWidget *parent) :
    InnerList(name, parent)
{
    score = sc;
    setObjectName("Staff");
    setStyleSheet(
                "Staff {"
                "border: 2px solid black;"
                "}"
        );

    layout->setMargin(5);


    setButtonText("Add Voice");

    setDraggableType("Staff");

    // setAcceptedDrops
    QSet<QString> tmp;
    tmp.insert("VoiceWidget");

    connect(this, SIGNAL(rename(ListItem*,QString)), score, SLOT(elementRenamed(ListItem*,QString)));
    connect(this, SIGNAL(moved(ListItem*,ListItem*)), score, SLOT(elementMoved(ListItem*,ListItem*)));

    setAcceptedDrops(tmp);
}

QWidget * Staff::defaultElement()
{
    return new VoiceWidget("voice", score);
}

