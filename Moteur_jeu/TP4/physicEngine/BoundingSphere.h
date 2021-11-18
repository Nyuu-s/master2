#ifndef BOUNDINGSPHERE_H
#define BOUNDINGSPHERE_H

#include <QVector3D>
#include "intersectdata.h"

class BoundingSphere
{
public:
    BoundingSphere(const QVector3D& center, float radius) :
    m_center(center),
    m_radius(radius)
    {};

    IntersectData instersectBoundingSphere(const BoundingSphere& other );


    inline const QVector3D& getCenter() const { return m_center;}
    inline float            getRadius() const { return m_radius;}
private:
    QVector3D m_center;
    float m_radius;

};

#endif // BOUNDINGSPHERE_H
