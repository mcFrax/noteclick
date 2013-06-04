#ifndef NOTEVALUE_H
#define NOTEVALUE_H

typedef double Duration; //prawdopodobnie to sie zmieni

class NoteValue
{
    friend Duration operator + (const NoteValue& nv1, const NoteValue& nv2);
    friend Duration operator + (const Duration& nv1, const NoteValue& nv2);
    friend Duration operator + (const NoteValue& nv1, const Duration& nv2);
    double baseval;
    int dotsVal;
public:
    NoteValue(double val = 1, int dots = 0);
    NoteValue(const NoteValue& copy);

    NoteValue dotted() const; //dodaj kropke
    int dots() const;

    Duration duration() const; //rzeczywista dlugosc
};

Duration operator + (const NoteValue& nv1, const NoteValue& nv2);
Duration operator + (const Duration& nv1, const NoteValue& nv2);
Duration operator + (const NoteValue& nv1, const Duration& nv2);

#endif // NOTEVALUE_H
