#ifndef BOUNDINGSPHERE_H
#define BOUNDINGSPHERE_H

#include <QVector3D>
#include "intersectdata.h"
#include "collider.h"

class BoundingSphere : public Collider
{
public:
    BoundingSphere(const QVector3D& center, float radius) :
    Collider(Collider::TYPE_SPHERE),
    m_center(center),
    m_radius(radius)
    {};

    IntersectData instersectBoundingSphere(const BoundingSphere& other );
    virtual void Transform(const QVector3D& translation);

    inline virtual QVector3D getCenter() const { return m_center;}
    inline float             getRadius() const { return m_radius;}
private:
    QVector3D m_center;
    float m_radius;

};

#endif // BOUNDINGSPHERE_H
