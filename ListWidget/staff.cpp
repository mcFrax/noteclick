#include "staff.h"

#include "voicewidget.h"

using namespace StructureView;


Staff::Staff(QString name, Score *sc, QWidget *parent) :
    InnerList(name, parent)
{
    score = sc;
    setObjectName("Staff");
    setStyleSheet(
                "StructureView--Staff {"
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
    connect(this, SIGNAL(removed(ListItem*)), score, SLOT(elementRemoved(ListItem*)));

    setAcceptedDrops(tmp);
}

QWidget * Staff::defaultElement()
{
    return new VoiceWidget("voice", score);
}

void Staff::slotAddElement()
{
    score->elementAdded(UserAction::CreateVoice, this); //userAction(UserAction);
}
