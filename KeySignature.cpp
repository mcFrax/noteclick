#include "KeySignature.h"

KeySignature::KeySignature(ToneEnume tonic, ScaleType type)
    : tonicVal(tonic), typeVal(type)
{
}

KeySignature::KeySignature(const Representation &representation)
{
#warning nie ma!
}

KeySignature::~KeySignature()
{
}

KeySignature::ToneEnum KeySignature::tonic()
{
    return tonicVal;
}

KeySignature::ScaleType KeySignature::type()
{
    return typeVal;
}

KeySignature::Representation KeySignature::representation(ClefInfo clef)
{
#warning też nie ma!
}
