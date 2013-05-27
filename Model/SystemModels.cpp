#include "SystemModels.h"

using namespace Model;

// ------------------------------- SYSTEM -------------------------------
System::System() :
    ModelBase()
{
}

System::System(IdRegister& registered_in, QObject * parent) :
    ModelBase(registered_in, parent)
{
}

System::~System()
{
}

// ------------------------------- STAFFSYSTEM -------------------------------
StaffSystem::StaffSystem() :
    ModelBase()
{
}

StaffSystem::StaffSystem(IdRegister& registered_in, QObject * parent) :
    ModelBase(registered_in, parent)
{
}

StaffSystem::~StaffSystem()
{
}

// --------------------------- STAFFSYSTEMELEMENT ---------------------------
StaffSystemElement::StaffSystemElement() :
    ModelBase(), position(StaffCoords())
{
}

StaffSystemElement::StaffSystemElement(IdRegister& registered_in, QObject * parent, StaffCoords coords) :
    ModelBase(registered_in, parent), position(coords)
{
}

StaffSystemElement::StaffSystemElement(IdRegister& registered_in, QObject * parent, qreal coord_x, qreal coord_y) :
    ModelBase(registered_in, parent), position(StaffCoords(coord_x, coord_y))
{
}

StaffSystemElement::~StaffSystemElement()
{
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

inline bool operator < (const StaffSystemElement& s1, const StaffSystemElement& s2)
{
    return s1.compare(s2) < 0;
}

// ------------------------------- CLEF -------------------------------
Clef::Clef() :
    StaffSystemElement(), info(ClefInfo())
{
}

Clef::Clef(IdRegister& registered_in, QObject *parent, StaffCoords coords) :
    StaffSystemElement(registered_in, parent, coords), info(ClefInfo())
{
}

Clef::Clef(IdRegister& registered_in, ClefInfo c_info, ModelBase * parent, StaffCoords coords) :
    StaffSystemElement(registered_in, parent, coords), info(c_info)
{
}

Clef::~Clef()
{
}

//// ------------------------------- KEYSIGNATURE-------------------------------
//KeySignature::KeySignature() :
//    ModelBase(), position(StaffCoords())
//{
//}

//KeySignature::KeySignature(IdRegister& registered_in, ModelBase * parent) :
//    ModelBase(registered_in, parent), position(StaffCoords())
//{
//}

//KeySignature::~KeySignature()
//{
//}

//// ------------------------------- TIMESIGNATURE -------------------------------
//TimeSignature::TimeSignature() :
//    ModelBase()
//{
//}

//TimeSignature::TimeSignature(IdRegister& registered_in, QObject * parent) :
//    ModelBase(registered_in, parent)
//{
//}

//TimeSignature::~TimeSignature()
//{
//}
