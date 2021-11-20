#ifndef PLANE_H
#define PLANE_H

#include <QVector3D>
#include "intersectdata.h"
#include "BoundingSphere.h"
#include "math.h"

class Plane
{
public:
    Plane(const QVector3D& normal, const float distance) :
    m_normal(normal),
    m_distance(distance)
    {};

    Plane Normalize();
    IntersectData intersectSphere(const BoundingSphere& sphere);


    inline const QVector3D getNormal() const {return m_normal;}
    inline float getDistance() const {return m_distance;}

private:
   const QVector3D m_normal;
    const float m_distance;
};

#endif // PLANE_H
