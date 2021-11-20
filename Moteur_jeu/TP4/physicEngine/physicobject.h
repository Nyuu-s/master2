#ifndef PHYSICOBJECT_H
#define PHYSICOBJECT_H

#include "BoundingSphere.h"
#include <QVector3D>


class PhysicObject
{
public:
    PhysicObject(const QVector3D& position, const QVector3D& velocity, float radius) :
     m_position(position),
     m_oldPosition(position),
     m_velocity(velocity),
     m_radius(radius),
     m_boundingSphere(position, radius)
    {};


    void Intergrate(float delta);

    inline const QVector3D getPosition() const { return m_position;}
    inline const QVector3D getVelocity() const { return m_velocity;}
    inline  float getRadius() const { return m_radius;}
    inline const Collider& getBoundingSphere() {
        QVector3D translation = m_position - m_oldPosition;
        m_oldPosition = m_position;
        m_boundingSphere.Transform(translation);

        return m_boundingSphere;
    }
    inline void setVelocity(QVector3D vel){
        m_velocity = vel;
    }
private:
    QVector3D m_position;
    QVector3D m_oldPosition;
    QVector3D m_velocity;
    float m_radius;
    BoundingSphere m_boundingSphere;
};

#endif // PHYSICOBJECT_H
