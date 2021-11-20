#ifndef PHYSICOBJECT_H
#define PHYSICOBJECT_H

#include "BoundingSphere.h"
#include <QVector3D>


class PhysicObject
{
public:
    PhysicObject(Collider* collider,  const QVector3D& velocity) :
     m_position(collider->getCenter()),
     m_oldPosition(collider->getCenter()),
     m_velocity(velocity),
     m_collider(collider)
    {};

    PhysicObject(const PhysicObject& other);
    virtual ~PhysicObject();


    void Intergrate(float delta);

    inline const QVector3D getPosition() const { return m_position;}
    inline const QVector3D getVelocity() const { return m_velocity;}

    inline const Collider& getCollider() {
        QVector3D translation = m_position - m_oldPosition;
        m_oldPosition = m_position;
        m_collider->Transform(translation);

        return *m_collider;
    }
    inline void setVelocity(QVector3D vel){
        m_velocity = vel;
    }
private:
    QVector3D m_position;
    QVector3D m_oldPosition;
    QVector3D m_velocity;

    Collider* m_collider;
};

#endif // PHYSICOBJECT_H
