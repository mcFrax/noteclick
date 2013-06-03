#include "ClefInfo.h"

ClefInfo::ClefInfo()
    : typeVal(Invalid), position(0), octave(0)
{
}

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
    if (typeVal == Invalid)
        return ~unsigned(0) >> 1; //cokolwiek
    else
        return position - typeVal - octave*8;
}

bool ClefInfo::isValid() const
{
    return typeVal != Invalid;
}

