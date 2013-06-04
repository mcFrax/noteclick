#include "NoteValue.h"

#include <cmath>

NoteValue::NoteValue(double val, int dots)
    : baseval(val), dotsVal(dots)
{
}

NoteValue::NoteValue(const NoteValue& copy) :
    baseval(copy.baseval), dotsVal(copy.dotsVal)
{
}

NoteValue NoteValue::dotted() const
{
    return NoteValue(baseval, dotsVal+1);
}

int NoteValue::dots() const
{
    return dotsVal;
}

Duration NoteValue::duration() const
{
    if (dotsVal == 0)
        return baseval;
    else
        return pow(1.5, dotsVal)*baseval;
}

Duration operator + (const NoteValue& nv1, const NoteValue& nv2)
{
    return nv1.duration() + nv2.duration();
}

Duration operator + (const Duration& d, const NoteValue& nv)
{
    return d + nv.duration();
}

Duration operator + (const NoteValue& nv, const Duration& d)
{
    return d + nv.duration();
}
