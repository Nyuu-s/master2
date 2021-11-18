#include "physicobject.h"

void PhysicObject::Intergrate(float delta){
    m_position += m_velocity * delta;
}
