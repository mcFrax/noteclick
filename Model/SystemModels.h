#ifndef SYSTEMMODELS_H
#define SYSTEMMODELS_H

#include <QList>
#include <QMap>
#include <QString>
#include "ModelBase.h"
#include "StaffCoords.h"
#include "ClefInfo.h"

namespace Model {

class SystemImage
{
public:
    SystemImage(QString filename = "");
    ~SystemImage();
protected:
    QString filename;
};

// -----------------------------------------------------------------------------

class System: public ModelBase // a.k.a. Page
{
public:
    explicit System();
    explicit System(IdRegister& registered_in, QObject * parent = 0);
    ~System();
protected:
    QList<SystemImage> image_list;
};

// -----------------------------------------------------------------------------

class StaffSystemElement; // forward declaration

class StaffSystem: public ModelBase {
public:
    explicit StaffSystem();
    explicit StaffSystem(IdRegister& registered_in, QObject * parent = 0);
    ~StaffSystem();
//    void addElement(StaffSystemElement &sse);
protected:
    QMap<StaffCoords, StaffSystemElement> elements;
};

// -----------------------------------------------------------------------------

class StaffSystemElement: public ModelBase {
public:
    explicit StaffSystemElement();
    explicit StaffSystemElement(IdRegister& registered_in, QObject * parent = 0, StaffCoords coords = StaffCoords());
    explicit StaffSystemElement(IdRegister& registered_in, QObject * parent = 0, qreal coord_x = 0, qreal coord_y = 0);
    ~StaffSystemElement();
public:
    int compare(const StaffSystemElement& sse2) const;
    bool inline operator=(const StaffSystemElement& sse2) const;
    StaffCoords getCoords();
protected:
    StaffCoords position;
};

// -----------------------------------------------------------------------------

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

// -----------------------------------------------------------------------------

class KeySignature: public ModelBase {
public:
    explicit KeySignature();
    explicit KeySignature(IdRegister& registered_in, ModelBase * parent = 0);
    ~KeySignature();
private:
    StaffCoords position;
    //KeySignatureInfo signature;
};

// -----------------------------------------------------------------------------

class TimeSignature: public ModelBase {
public:
    explicit TimeSignature();
    explicit TimeSignature(IdRegister& registered_in, QObject * parent = 0);
    ~TimeSignature();
};

}

#endif // SYSTEMMODELS_H
