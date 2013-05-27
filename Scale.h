#ifndef SCALE_H
#define SCALE_H

/*! Numer dzwieku w skali.
 *
 * Numer dzwieku w skali. Odpowiada pozycji nuty/chromatyki na pieciolinii.
 * 0 = dzwiek bazowy (first degree, tonic).
 *
 * http://en.wikipedia.org/wiki/Degree_%28music%29
 */
typedef int ScaleDegree;

typedef int Pitch;

enum PitchEnum
{
    cPitch = 0,
    cisPitch = 1,
    desPitch = 1,
    dPitch = 2,
    disPitch = 3,
    eesPitch = 3,
    ePitch = 4,
    fPitch = 5,
    fisPitch = 6,
    gesPitch = 6,
    gPitch = 7,
    gisPitch = 8,
    aesPitch = 8,
    aPitch = 9,
    aisPitch = 10,
    besPitch = 10,
    bPitch = 11
};

class AbstractScale
{
protected:
    AbstractScale() = default;
public:
    virtual QString name() const;
    virtual bool isDiatonic() const;
    virtual bool isMajor() const;
    virtual bool isMinor() const;

    virtual ScaleDegree toCMajor(ScaleDegree degree) const;
    virtual Pitch pitch(ScaleDegree degree) const;
    virtual ScaleDegree degree(Pitch pitch) const;
};

class DiatonicScale : public AbstractScale
{
    Pitch firstDegree;
public:
    DiatonicScale(Pitch firstDegree);
    virtual bool isDiatonic() const;

};

class MajorScale : public DiatonicScale
{
    Pitch firstDegree;
public:
    DiatonicScale(Pitch firstDegree);
    virtual bool isDiatonic() const;

#endif // SCALE_H
