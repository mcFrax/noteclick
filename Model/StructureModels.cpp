#include "StructureModels.h"

using namespace Model;

// ------------------------------- CHOIRGROUP -------------------------------
ChoirGroup::ChoirGroup() :
    ModelBase()
{
}

ChoirGroup::ChoirGroup(ScoreModel *sm_ptr, IdRegister& registered_in, QObject * parent) :
    ModelBase(sm_ptr, registered_in, parent)
{
}

ChoirGroup::~ChoirGroup()
{
}

// ------------------------------- STAFF -------------------------------
Staff::Staff() :
    ModelBase()
{
}

Staff::Staff(ScoreModel *sm_ptr, IdRegister& registered_in, QObject * parent) :
    ModelBase(sm_ptr, registered_in, parent)
{
}

Staff::~Staff()
{
}

// ------------------------------- VOICE -------------------------------
Voice::Voice() :
    ModelBase()
{
}

Voice::Voice(ScoreModel *sm_ptr, IdRegister& registered_in, QObject * parent) :
    ModelBase(sm_ptr, registered_in, parent)
{
}

Voice::~Voice()
{
    // TODO: pewnie okaze sie konieczne przejscie po wszystkich dzieciach i usuniecie osobno
}
