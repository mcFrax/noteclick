#include "ClefInfo.h"

ClefInfo::ClefInfo(ClefType type, int position, int octave)
    : typeVal(type), position(position), octave(octave)
{
}

ClefInfo::ClefType ClefInfo::type() const
{
    return typeVal;
}

int ClefInfo::positionOnStaff() const
{
    return position;
}

int ClefInfo::octaveTransposition() const
{
    return octave;
}

int ClefInfo::middleCPositionOnStaff() const
{
    return position - typeVal - octave*8;
}

