#include "collider.h"
#include "BoundingSphere.h"
#include <iostream>

IntersectData Collider::Intersect(const Collider& other) const
{
    if(this->getType() == TYPE_SPHERE && other.getType() == TYPE_SPHERE )
    {
        BoundingSphere *self = (BoundingSphere*)this;
        return self->instersectBoundingSphere((BoundingSphere&)other);
    }

    std::cout << "error";
    exit(1);
    return IntersectData(false, QVector3D());
}


