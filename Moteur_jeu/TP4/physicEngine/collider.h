#ifndef COLLIDER_H
#define COLLIDER_H

#include <QVector3D>
#include "ReferenceCounter.h"
#include "intersectdata.h"
class Collider : public ReferenceCounter
{
public:
    enum
    {
         TYPE_SPHERE,
         TYPE_AABB,
         TYPE_PLANE,

         TYPE_SIZE
    };
    Collider(int type):
        ReferenceCounter(),
        m_type(type)
    {};

    inline int getType() const {return m_type;}

    IntersectData Intersect(const Collider& other) const;
    virtual void Transform(const QVector3D& translation){};
    inline virtual QVector3D getCenter() const {return QVector3D();}

private:
    int m_type;
};

#endif // COLLIDER_H
