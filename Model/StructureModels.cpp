#include "StructureModels.h"

using namespace Model;

// ------------------------------- CHOIRGROUP -------------------------------
ChoirGroup::ChoirGroup() :
    ModelBase()
{
}

ChoirGroup::ChoirGroup(IdRegister& registered_in, QObject * parent) :
    ModelBase(registered_in, parent)
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

Staff::Staff(IdRegister& registered_in, QObject * parent) :
    ModelBase(registered_in, parent)
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

Voice::Voice(IdRegister& registered_in, QObject * parent) :
    ModelBase(registered_in, parent)
{
}

Voice::~Voice()
{
}
