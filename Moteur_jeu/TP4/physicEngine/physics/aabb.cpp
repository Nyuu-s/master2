#include "aabb.h"


IntersectData AABB::IntersectAABB(const AABB& other){
    QVector3D distances1 = other.getMinCorner() - m_maxCorner;
    QVector3D distances2 = m_minCorner - other.getMaxCorner();
    QVector3D distances = Transform::VecMax(distances1, distances2);

    float maxDistance = Transform::VecMaxValue(distances);

    return IntersectData(maxDistance < 0, distances);
}
