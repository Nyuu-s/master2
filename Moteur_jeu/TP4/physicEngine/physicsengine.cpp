#include "physicsengine.h"
#include "stdio.h"

PhysicsEngine::PhysicsEngine()
{

}


void PhysicsEngine::AddObject(const PhysicObject& object)
{
    m_objects.push_back(object);
}

void PhysicsEngine::Simulate(float delta)
{
    for(unsigned int i=0; i<m_objects.size(); i++){
        m_objects[i].Intergrate(delta);
    }
}

void PhysicsEngine::HandleCollisions(){
    for(unsigned int i=0; i<m_objects.size(); i++){
        for(unsigned int j=i+1; j<m_objects.size(); j++){
            IntersectData intersect = m_objects[i].getBoundingSphere().Intersect(m_objects[j].getBoundingSphere());
            if(intersect.IsIntersect()){
                m_objects[i].setVelocity(m_objects[i].getVelocity() * -1);
                m_objects[j].setVelocity(m_objects[j].getVelocity() * -1);
            }
        }
    }
}
