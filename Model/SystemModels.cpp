#include "SystemModels.h"

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

//void StaffSystem::addElement(StaffSystemElement &sse)
//{
//    elements.insert(sse.getCoords(), sse);
//}

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
