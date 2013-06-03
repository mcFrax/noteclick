#ifndef CLEFINFO_H
#define CLEFINFO_H

class ClefInfo
{
public:
    enum ClefType
    {
        GClef = 4,
        FClef = -4,
        CClef = 0,
        Invalid
    };
protected:
    ClefType typeVal;
    int position;
    int octave;
public:
    ClefInfo();
    ClefInfo(ClefType type, int position, int octave = 0);

    ClefType type() const;
    int positionOnStaff() const;
    int octaveTransposition() const;

    int middleCPositionOnStaff() const;

    bool isValid() const;
};

#endif // CLEFINFO_H
