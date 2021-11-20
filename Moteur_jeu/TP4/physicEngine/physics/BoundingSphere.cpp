#include "BoundingSphere.h"

IntersectData BoundingSphere::instersectBoundingSphere(const BoundingSphere& other){
    float radiusDistance = m_radius + other.getRadius();

    QVector3D direction = (other.getCenter()- m_center);
    float centerDistance = direction.length();
    direction /= centerDistance; // normalize direction

    float distance = centerDistance - radiusDistance;
    return IntersectData(centerDistance < radiusDistance, direction * distance );
}


void BoundingSphere::Transform(const QVector3D& translation){
    m_center += translation;
};
