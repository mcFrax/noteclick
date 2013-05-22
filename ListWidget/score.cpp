#include "score.h"
#include "choirgroup.h"
#include "staff.h"
#include "voicewidget.h"

//TMP
#include <QMessageBox>

Score::Score(QWidget *parent, QString name) :
    ListWidget(name, parent)
{
    setObjectName("Score");
    setStyleSheet(
        "Score {"
        "border-left: 0px;"
        "background-color: white;"
        "border-top: 1 px solid black;"
        "border-bottom: 1 px solid black;}"
        );

    setButtonText("Add ChoirGroup");

    setDraggableType("Score");

    // setAcceptedDrops
    QSet<QString> tmp;
    tmp.insert("ChoirGroup");

    setAcceptedDrops(tmp);

    /* TMP */
    addChoirGroup(1,0,"111");
    addChoirGroup(4,0,"4444");
    addStaff(2,1,"staff");
    addStaff(5,1,"555");

    addVoice(3,2,"voice");

    renameElement(1, "aaaa");
    renameElement(2, "bbbb");
    renameElement(3, "cccc");
    moveElement(2, 4);
    moveElement(3, 5);
}

QWidget * Score::defaultElement()
{
    return new ChoirGroup("choir", this);
}

void Score::addElement()
{
    box->addElement(defaultElement());
}


void Score::addChoirGroup(IdType id, IdType parentId, QString name)
{
    if (parentId == 0)
    {
        ChoirGroup *newElement = new ChoirGroup(name, this);
        pointers[id] = (void*) newElement;
        box->addElement(newElement);
    }
}


void Score::addStaff(IdType id, IdType parentId, QString name)
{
    ChoirGroup *parent =  (ChoirGroup*)pointers[parentId];
    Staff *newElement = new Staff(name, this);

    pointers[id] = newElement;
    parent->addElement(newElement);

}


void Score::addVoice(IdType id, IdType parentId, QString name)
{
    Staff *parent =  (Staff*)pointers[parentId];
    VoiceWidget *newElement = new VoiceWidget(name, this);

    pointers[id] = newElement;
    parent->addElement(newElement);

}

void Score::renameElement(IdType id, QString name)
{
    ListItem *element =  (ListItem*)pointers[id];

    element->setText(name);
}



void Score::moveElement(IdType id, IdType newParent)
{
    InnerList *parent = (InnerList*)pointers[newParent];
    ListItem *element = (ListItem*)pointers[id];
    parent->addElement(element);
}

void Score::removeElement(IdType id)
{
    ListItem *element = (ListItem*)pointers[id];
    delete element;
}

void Score::elementRemoved(ListItem *item)
{
    IdType id = pointers.key((void*)item);

    emit modelElementRemoved(id);
    //TMP
    removeElement(id);
}

void Score::elementRenamed(ListItem *item, QString name)
{
    IdType id = pointers.key((void*)item);

    emit modelElementRenamed(id, name);
    //TMP
    renameElement(id, name);

}

void Score::elementMoved(ListItem *item, ListItem *newParent)
{
    IdType id = pointers.key((void*)item);
    IdType pid = pointers.key((void*)newParent);
    emit modelElementMoved(id, pid);
    //TMP
    moveElement(id, pid);

}

void Score::scoreChange(ScoreChange change)
{
    try
    {
        switch (change.category)
        {
            case ScoreChange::StructureChanged:

                return;
            case ScoreChange::SystemChanged:
                //To nas nie obchodzi.
                return;
            case ScoreChange::ScoreChanged:
                //To nas nie obchodzi.
                return;
            //Nie wstawiac default!
            //Chodzi o to, zeby dostac warn w przypadku nieobslugiwania czegos.
        }

        //Tu trafiamy tylko w przypadku niepoprawnej wartosci action.category:
        emit error(tr("Invalid ScoreChange::category value ")+QString::number(change.category));
    }
    catch (std::bad_cast &e)
    {
        emit error(tr("std::bad_cast caught during ScoreChange handling: ")+e.what()+'\n'
                   +"VSA typeid = "+change.args.typeName());
    }
}


void Score::handleStructureChange(ScoreChange change)
{
    IdType mine, parent;
    QString name;

    switch (static_cast<ScoreChange::StructureChangeEnum>(change.change))
    {
        case ScoreChange::GroupCreated:          //(IdType id: IdType parent_id)
            change.args.unpackTo(mine, parent);
            addChoirGroup(mine, parent);
            return;
        case ScoreChange::StaffCreated:          //(IdType id: IdType parent_id)
            addStaff(mine, parent);
            return;
        case ScoreChange::VoiceCreated:          //(IdType id: IdType parent_id)
            change.args.unpackTo(mine, parent);
            addVoice(mine, parent);
            return;
        case ScoreChange::GroupMoved:            //(IdType id: IdType new_parent_id)
            change.args.unpackTo(mine, parent);
            return;
        case ScoreChange::StaffMoved:            //(IdType id: IdType new_parent_id)
            change.args.unpackTo(mine, parent);
            moveElement(mine, parent);
            return;
        case ScoreChange::VoiceMoved:            //(IdType id: IdType new_parent_id)
            moveElement(mine, parent);
            return;
        case ScoreChange::StructureObjectErased: //(IdType id)
            change.args.unpackTo(mine);
            remove(mine);
            return;
        case ScoreChange::StructureObjectRenamed:
            change.args.unpackTo(mine, name);
            rename(mine, name);
            return;
        //Nie wstawiac default!
        //Chodzi o to, zeby dostac warn w przypadku nieobslugiwania czegos.
    }

    //Tu trafiamy tylko w przypadku niepoprawnej wartosci action.action:
    emit error(tr("Invalid or unhandled ScoreChanged::change value (as ScoreChanged::StructureChanged) ")
            +QString::number(change.change));
}


