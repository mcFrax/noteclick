#ifndef SYSTEMMODELS_H
#define SYSTEMMODELS_H

#include "ModelBase.h"
#include "StaffCoords.h"
#include "ClefInfo.h"

namespace Model {

class System: public ModelBase // a.k.a. Page
{
public:
    explicit System();
    explicit System(IdRegister& registered_in, QObject * parent = 0);
    ~System();
private:
    //SystemImage img;
};

class StaffSystem: public ModelBase {
public:
    explicit StaffSystem();
    explicit StaffSystem(IdRegister& registered_in, QObject * parent = 0);
    ~StaffSystem();
};

class StaffSystemElement: public ModelBase {
public:
    explicit StaffSystemElement();
    explicit StaffSystemElement(IdRegister& registered_in, QObject * parent = 0, StaffCoords coords = StaffCoords());
    explicit StaffSystemElement(IdRegister& registered_in, QObject * parent = 0, qreal coord_x = 0, qreal coord_y = 0);
    ~StaffSystemElement();
public:
    int compare(const StaffSystemElement& sse2) const;
protected:
    StaffCoords position;
};

class Clef: public StaffSystemElement {
public:
    explicit Clef();
    explicit Clef(IdRegister& registered_in, QObject * parent = 0, StaffCoords coords = StaffCoords());
    explicit Clef(IdRegister& registered_in, ClefInfo c_info, ModelBase * parent = 0, StaffCoords coords = StaffCoords());
//    explicit Clef(IdRegister& registered_in, ClefType c_type, int c_position, int c_octave = 0, ModelBase * parent = 0);
    ~Clef();
private:
    ClefInfo info;
};

//class KeySignature: public ModelBase {
//public:
//    explicit KeySignature();
//    explicit KeySignature(IdRegister& registered_in, ModelBase * parent = 0);
//    ~KeySignature();
//private:
//    StaffCoords position;
//    //KeySignatureInfo signature;
//};

class TimeSignature: public ModelBase {
public:
    explicit TimeSignature();
    explicit TimeSignature(IdRegister& registered_in, QObject * parent = 0);
    ~TimeSignature();
};

}

#endif // SYSTEMMODELS_H
