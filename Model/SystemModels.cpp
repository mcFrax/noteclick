#include "SystemModels.h"
#include "../SignalCommunication/ScoreChange.h"

using namespace Model;

// ------------------------------- SYSTEMIMAGE ---------------------------
SystemImage::SystemImage(QString filename) :
    filename(filename)
{
}

SystemImage::~SystemImage()
{
}

// ------------------------------- SYSTEM -------------------------------
System::System() :
    ModelBase()
{
}

System::System(ScoreModel *sm_ptr, IdRegister& registered_in, QObject * parent) :
    ModelBase(sm_ptr, registered_in, parent)
{
}

System::~System()
{
}

void System::complementCreationList(QList<ScoreChange> *list)
{
//    list->append();
    for (QLinkedList<ModelBase*>::Iterator it = children.begin(); it != children.end(); ++it)
        (*it)->complementCreationList(list);
}

// ------------------------------- STAFFSYSTEM -------------------------------
StaffSystem::StaffSystem() :
    ModelBase()
{
}

StaffSystem::StaffSystem(ScoreModel *sm_ptr, IdRegister& registered_in, QObject * parent) :
    ModelBase(sm_ptr, registered_in, parent)
{
}

StaffSystem::~StaffSystem()
{
}

void StaffSystem::addElement(StaffSystemElement *sse)
{
    elements.insert(sse->getCoords(), sse);
}

QMultiMap<StaffCoords, StaffSystemElement*>::Iterator StaffSystem::findMe(StaffSystemElement *child_sse)
{
    return elements.find(child_sse->getCoords(), child_sse);
}

bool StaffSystem::amIFirst(StaffSystemElement *child_sse)
{
    return findMe(child_sse) == elements.begin() + 1;
}

bool StaffSystem::amILast(StaffSystemElement *child_sse)
{
    return findMe(child_sse) == elements.end() - 1;
}

void StaffSystem::complementCreationList(QList<ScoreChange> *list)
{
    list->append(ScoreChange(ScoreChange::StaffSystemCreated, vsa(this->id() /* jeszcze 2 argumenty */)));
    for (QLinkedList<ModelBase*>::Iterator it = children.begin(); it != children.end(); ++it)
        (*it)->complementCreationList(list);
}

// --------------------------- STAFFSYSTEMELEMENT ---------------------------
StaffSystemElement::StaffSystemElement() :
    ModelBase(), position(StaffCoords())
{
}

StaffSystemElement::StaffSystemElement(ScoreModel *sm_ptr, IdRegister& registered_in, QObject * parent, StaffCoords coords) :
    ModelBase(sm_ptr, registered_in, parent), position(coords)
{
}

StaffSystemElement::StaffSystemElement(ScoreModel *sm_ptr, IdRegister& registered_in, QObject * parent, qreal coord_x, qreal coord_y) :
    ModelBase(sm_ptr, registered_in, parent), position(StaffCoords(coord_x, coord_y))
{
}

StaffSystemElement::~StaffSystemElement()
{
}

StaffCoords StaffSystemElement::getCoords()
{
    return position;
}

int StaffSystemElement::compare(const StaffSystemElement& sse2) const
{
    if (this->position < sse2.position)
        return -1;
    else if (this->position == sse2.position)
        return 0;
    else
        return 1;
}

inline bool operator< (const StaffSystemElement& s1, const StaffSystemElement& s2)
{
    return s1.compare(s2) < 0;
}

inline bool StaffSystemElement::operator= (const StaffSystemElement& sse2) const
{
    return compare(sse2) == 0;
}

StaffSystemElement * StaffSystemElement::previous()
{
    StaffSystem *dad = static_cast<StaffSystem*>(parent());
    if (!dad->amIFirst(this))
        return (--(dad->findMe(this))).value();
    else
        return NULL;
}

StaffSystemElement * StaffSystemElement::next()
{
    StaffSystem *dad = static_cast<StaffSystem*>(parent());
    if (!dad->amILast(this))
        return (++(dad->findMe(this))).value();
    else
        return NULL;
}

// ------------------------------- CLEF -------------------------------
Clef::Clef() :
    StaffSystemElement(), info(ClefInfo())
{
}

Clef::Clef(ScoreModel *sm_ptr, IdRegister& registered_in, QObject *parent, StaffCoords coords) :
    StaffSystemElement(sm_ptr, registered_in, parent, coords), info(ClefInfo())
{
}

Clef::Clef(ScoreModel *sm_ptr, IdRegister& registered_in, ClefInfo c_info, ModelBase * parent, StaffCoords coords) :
    StaffSystemElement(sm_ptr, registered_in, parent, coords), info(c_info)
{
}

Clef::~Clef()
{
}

void Clef::complementCreationList(QList<ScoreChange> *list)
{
    list->append(ScoreChange(ScoreChange::ClefCreated, vsa(this->id(), 0, position, info /* jeszcze 1 argument */)));

//    for (QLinkedList<ModelBase*>::Iterator it = children.begin(); it != children.end(); ++it)
//        (*it)->complementCreationList(list);
}

// ------------------------------- KEYSIGNATURE-------------------------------
KeySignature::KeySignature() :
    ModelBase(), position(StaffCoords())
{
}

KeySignature::KeySignature(ScoreModel *sm_ptr, IdRegister& registered_in, ModelBase * parent) :
    ModelBase(sm_ptr, registered_in, parent), position(StaffCoords())
{
}

KeySignature::~KeySignature()
{
}

void KeySignature::complementCreationList(QList<ScoreChange> *list)
{
    list->append(ScoreChange(ScoreChange::KeySignatureCreated, vsa(this->id(), 0, position, signature /* jeszcze 1 argument */)));

//    for (QLinkedList<ModelBase*>::Iterator it = children.begin(); it != children.end(); ++it)
//        (*it)->complementCreationList(list);
}

// ------------------------------- TIMESIGNATURE -------------------------------
TimeSignature::TimeSignature() :
    ModelBase()
{
}

TimeSignature::TimeSignature(ScoreModel *sm_ptr, IdRegister& registered_in, QObject * parent) :
    ModelBase(sm_ptr, registered_in, parent)
{
}

TimeSignature::~TimeSignature()
{
}

void TimeSignature::complementCreationList(QList<ScoreChange> *list)
{
    list->append(ScoreChange(ScoreChange::TimeSignatureCreated, vsa(this->id(), 0, position, signature /* jeszcze 1 argument */)));

//    for (QLinkedList<ModelBase*>::Iterator it = children.begin(); it != children.end(); ++it)
//        (*it)->complementCreationList(list);
}
