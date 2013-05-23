#ifndef CLEFINFO_H
#define CLEFINFO_H

class ClefInfo
{
    ClefType typeVal;
    int position;
    int octave;
public:
    enum ClefType
    {
        GClef = 4,
        FClef = -4,
        CClef = 0
    };

    ClefInfo(ClefType type, int position, int octave = 0);

    ClefType type() const;
    int positionOnStaff() const;
    int octaveTransposition() const;

    int middleCPositionOnStaff() const;
};

#endif // CLEFINFO_H
