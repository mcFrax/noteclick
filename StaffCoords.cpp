#include "StaffCoords.h"

#include <cmath>


static const QPolygonF oneSquare = QPolygonF() << QPointF(0, 0) << QPointF(1, 0)
                                               << QPointF(1, 1) << QPointF(0, 1);

//=============//
// StaffCoords //
//=============//

StaffCoords::StaffCoords()
{
}

StaffCoords::StaffCoords(qreal x, qreal y)
    : QPointF(x, y)
{
}

StaffCoords::StaffCoords(const QPointF & p)
    : QPointF(p)
{
}

void StaffCoords::roundToDegree()
{
    setY(round(y()*8)/8.0);
}

StaffCoords StaffCoords::roundedToDegree() const
{
    return StaffCoords(x(), round(y()*8)/8.0);
}

ScaleDegree StaffCoords::degree() const
{
    return round(y()*8);
}


//===============//
// StaffPosition //
//===============//

//==============//
// Constructors //
//==============//


StaffPosition::StaffPosition(const QPointF & tl, const QPointF & tr, const QPointF & bl, const QPointF & br)
{
    polygon << tl << tr << bl << br;
    recalcMatrices();
}

//uwaga - nie sprawdza poprawnosci
StaffPosition::StaffPosition(const QPolygonF& p)
    : polygon(p)
{
    recalcMatrices();
}

StaffPosition::StaffPosition()
    : polygon(oneSquare)
{
    recalcMatrices();
}

//==================//
// transformation() //
//==================//

void StaffPosition::recalcMatrices()
{
    QTransform::quadToQuad(polygon, oneSquare, transformation);
    QTransform::quadToQuad(oneSquare, polygon, backTransformation);
}

const QTransform &StaffPosition::toStaffTransformation() const
{
    return transformation;
}

const QTransform &StaffPosition::fromStaffTransformation() const
{
    return backTransformation;
}

//===============//
// toQPolygonF() //
//===============//

QPolygonF StaffPosition::toQPolygonF() const
{
    return polygon;
}

//===================//
// Coords conversion //
//===================//

StaffCoords StaffPosition::toStaffCoords(QPointF coords) const
{
    return coords * transformation;
}

QPointF StaffPosition::fromStaffCoords(StaffCoords coords) const
{
    return coords * backTransformation;
}


//=================//
// getters/setters //
//=================//

QPointF StaffPosition::topLeft() const
{
    return polygon[0];
}

QPointF StaffPosition::topRight() const
{
    return polygon[1];
}

QPointF StaffPosition::bottomLeft() const
{
    return polygon[3];
}

QPointF StaffPosition::bottomRight() const
{
    return polygon[2];
}

void StaffPosition::setTopLeft(const QPointF & p)
{
    polygon[0] = p;
}

void StaffPosition::setTopRight(const QPointF & p)
{
    polygon[1] = p;
}

void StaffPosition::setBottomLeft(const QPointF & p)
{
    polygon[3] = p;
}

void StaffPosition::setBottomRight(const QPointF & p)
{
    polygon[2] = p;
}


