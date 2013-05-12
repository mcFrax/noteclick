#ifndef STAFFCOORDS_H
#define STAFFCOORDS_H

#include <QPointF>
#include <QTransform>
#include <QPolygonF>

#warning ma byc zastapione prawdziwym ScaleDegree
typedef int ScaleDegree;

//! Wspolrzedne na pieciolinii
struct StaffCoords : public QPointF
{
    //Wspolrzedne oznaczaja to, co widac:
    //                               A
    // -0------------x------------1--+-->
    //  __,________________________  |__1
    //  ==|)==#=4==================  |
    //  =(@)=#==4==================  |__0
    //    J                          | y

    StaffCoords();
    StaffCoords(qreal x, qreal y);
    StaffCoords(const QPointF&);

    //Zaokraglanie y, żeby odpowiadal lezeniu na linii/srodku pola.
    void roundToDegree();
    StaffCoords roundedToDegree() const;

    ScaleDegree degree() const;
};

inline bool operator < (const StaffCoords& c1, const StaffCoords& c2)
{
    return c1.x() < c2.y();
}


//! Pozycja pieciolinii (umieszczenie Staff-a na SystemImage)
class StaffPosition
{
    QPolygonF polygon;
    QTransform transformation;
    QTransform backTransformation;
    void recalcMatrices();

    StaffPosition(const QPolygonF&); //schowane, poki nie ma spojnej polityki wyjatkow; na razie nie sprawdza poprawnosci
public:
    StaffPosition(const QPointF&, const QPointF&, const QPointF&, const QPointF&);

    QPointF topLeft() const;
    QPointF topRight() const;
    QPointF bottomLeft() const;
    QPointF bottomRight() const;

    void setTopLeft(const QPointF&);
    void setTopRight(const QPointF&);
    void setBottomLeft(const QPointF&);
    void setBottomRight(const QPointF&);

    QPolygonF toQPolygonF() const;

    const QTransform& toStaffTransformation() const;
    const QTransform& fromStaffTransformation() const;

    //transformacja wspolrzednych
    QPointF fromStaffCoords(StaffCoords coords) const;
    StaffCoords toStaffCoords(QPointF coords) const;
};


#endif // STAFFCOORDS_H
