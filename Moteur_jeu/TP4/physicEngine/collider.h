#ifndef COLLIDER_H
#define COLLIDER_H

#include "intersectdata.h"

class Collider
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
        m_type(type)
    {};

    inline int getType() const {return m_type;}

    IntersectData Intersect(const Collider& other);

private:
    int m_type;
};

#endif // COLLIDER_H
