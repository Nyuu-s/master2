#ifndef PHYSICOBJECT_H
#define PHYSICOBJECT_H

#include "BoundingSphere.h"
#include <QVector3D>


class PhysicObject
{
public:
    PhysicObject(const QVector3D& position, const QVector3D& velocity, float radius) :
     m_position(position),
     m_velocity(velocity),
     m_radius(radius)
    {};


    void Intergrate(float delta);

    inline const QVector3D getPosition() const { return m_position;}
    inline const QVector3D getVelocity() const { return m_velocity;}
    inline  float getRadius() const { return m_radius;}
    inline BoundingSphere getBoundingSphere() {
        return BoundingSphere(m_position, m_radius);
    }
    inline void setVelocity(QVector3D vel){
        m_velocity = vel;
    }
private:
    QVector3D m_position;
    QVector3D m_velocity;
    float m_radius;
};

#endif // PHYSICOBJECT_H
