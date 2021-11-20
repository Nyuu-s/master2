#include "plane.h"

Plane Plane::Normalize(){
    float magnitude = m_normal.length();
    return Plane(m_normal / magnitude,m_distance/magnitude);
}

IntersectData Plane::intersectSphere(const BoundingSphere& sphere){

    float distFromSphereCenter = fabs(QVector3D::dotProduct(sphere.getCenter(), m_normal) + m_distance);
    float distanceFromSphere = distFromSphereCenter - sphere.getRadius();
    return IntersectData(distanceFromSphere < 0 , m_normal * distanceFromSphere);
};
