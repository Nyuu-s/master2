#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "physicobject.h"
#include <vector>
#include "BoundingSphere.h"

class PhysicsEngine
{
public:
    PhysicsEngine();

    void AddObject(const PhysicObject& object);
    void Simulate(float delta);

    void HandleCollisions();

    inline PhysicObject& getObject(unsigned int index){
        return m_objects[index];
    }

    inline unsigned int getNumObjs(){
        return (unsigned int) m_objects.size();
    }
private:
    std::vector<PhysicObject> m_objects;

};

#endif // PHYSICSENGINE_H
