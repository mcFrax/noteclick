#ifndef KEYSIGNATURE_H
#define KEYSIGNATURE_H

#include <array>

class ClefInfo;

class KeySignature
{
public:
    //byc moze te enumy w przyszlosci wyleca gdzie indziej
    enum ChromaticMark
    {
        Natural,
        Sharp,
        Flat
    };

    enum ToneEnum
    {
        cTone = 0,
        cisTone = 1,
        desTone = 1,
        dTone = 2,
        disTone = 3,
        eesTone = 3,
        eTone = 4,
        fTone = 5,
        fisTone = 6,
        gesTone = 6,
        gTone = 7,
        gisTone = 8,
        aesTone = 8,
        aTone = 9,
        aisTone = 10,
        besTone = 10,
        bTone = 11
    };

    enum ScaleType
    {
        Minor = 0,
        Major = 1<<6
    };

    typedef std::array<ChromaticMark, 9> Representation;
private:
    ToneEnum tonicVal;
    ScaleType typeVal;
public:
    KeySignature(ToneEnume tonic = cTone, ScaleType type = Major);
    KeySignature(const Representation& representation);
    virtual ~KeySignature();

    ToneEnum tonic();
    ScaleType type();

    Representation representation(ClefInfo clef);

    QString name();
};

#endif // KEYSIGNATURE_H
