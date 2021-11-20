#include "BoundingSphere.h"

IntersectData BoundingSphere::instersectBoundingSphere(const BoundingSphere& other){
    float radiusDistance = m_radius + other.getRadius();
    float centerDistance = (other.getCenter()- m_center).length();
    float distance = centerDistance - radiusDistance;
    return IntersectData(centerDistance < radiusDistance, distance );
}


void BoundingSphere::Transform(const QVector3D& translation){
    m_center += translation;
};
