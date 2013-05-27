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

    pointers[0] = this;

    // setAcceptedDrops
    setDraggableType("Score");

    QSet<QString> tmp;
    tmp.insert("ChoirGroup");
    setAcceptedDrops(tmp);

    connect(this, SIGNAL(moved(ListItem*,ListItem*)), this, SLOT(elementMoved(ListItem*,ListItem*)));

    /*
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
    addVoice(6,2,"lolo");
*/
}

QWidget * Score::defaultElement()
{
    return new ChoirGroup("choir", this);
}

void Score::slotAddElement()
{
    elementAdded(UserAction::CreateGroup, this);
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

void Score::elementAdded(UserAction::StructureChangeEnum action, ListItem *pointer)
{
    //box->addElement(defaultElement());
    IdType pid = pointers.key((void*)pointer);

    UserAction a(action , vsa(pid));
    emit userAction(a);
}

void Score::elementRemoved(ListItem *item)
{
    IdType id = pointers.key((void*)item);

    UserAction a(UserAction::StructureObjectErase, vsa(id));
    emit userAction(a);
    //TMP
    //removeElement(id);
}

void Score::elementRenamed(ListItem *item, QString name)
{
    IdType id = pointers.key((void*)item);

    UserAction a(UserAction::StructureObjectRename , vsa(id, name));
    emit userAction(a);
    //emit modelElementRenamed(id, name);
    //TMP
    //renameElement(id, name);

}

void Score::elementMoved(ListItem *item, ListItem *newParent)
{

    IdType id = pointers.key((void*)item);
    IdType pid = pointers.key((void*)newParent);

    UserAction::StructureChangeEnum change;

    if (dynamic_cast<ChoirGroup*>(item) != NULL)
    {
        change = UserAction::MoveGroup;
    }
    else if (dynamic_cast<VoiceWidget*>(item) != NULL)
    {
        change = UserAction::MoveVoice;
    }
    else //(dynamic_cast<Staff*>(item) != NULL)
    {
        change = UserAction::MoveStaff;
    }


    UserAction a(change, vsa(id, pid));
    emit userAction(a);
    //emit modelElementMoved(id, pid);
    //TMP
    //moveElement(id, pid);

}


void Score::voiceSelected(void *p, bool state)
{
    if (!state)
    {
        selected = NULL;
        return;
    }

    if (selected != NULL)
    {
        selected->setSelected(false);
    }

    selected = (VoiceWidget*)p;
    IdType id = pointers.key(p);


    emit voiceSelectedSignal(id);
}

void Score::voiceChecked(void *p, bool state)
{
    IdType id = pointers.key(p);

    emit voiceCheckedSignal(id, state);
}


void Score::scoreChange(ScoreChange change)
{
    try
    {
        switch (change.category)
        {
            case ScoreChange::StructureChanged:
                handleStructureChange(change);
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
            change.args.unpackTo(mine, parent);
            addStaff(mine, parent);
            return;
        case ScoreChange::VoiceCreated:          //(IdType id: IdType parent_id)
            change.args.unpackTo(mine, parent);
            addVoice(mine, parent);
            return;
        case ScoreChange::GroupMoved:            //(IdType id: IdType new_parent_id)

        case ScoreChange::StaffMoved:            //(IdType id: IdType new_parent_id)

        case ScoreChange::VoiceMoved:            //(IdType id: IdType new_parent_id)
            change.args.unpackTo(mine, parent);
            moveElement(mine, parent);
            return;
        case ScoreChange::StructureObjectErased: //(IdType id)
            change.args.unpackTo(mine);
            removeElement(mine);
            return;
        case ScoreChange::StructureObjectRenamed:
            change.args.unpackTo(mine, name);
            renameElement(mine, name);
            return;
        //Nie wstawiac default!
        //Chodzi o to, zeby dostac warn w przypadku nieobslugiwania czegos.
    }

    //Tu trafiamy tylko w przypadku niepoprawnej wartosci action.action:
    emit error(tr("Invalid or unhandled ScoreChanged::change value (as ScoreChanged::StructureChanged) ")
            +QString::number(change.change));
}
