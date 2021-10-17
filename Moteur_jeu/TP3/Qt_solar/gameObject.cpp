#include "gameObject.h"

gameObject::gameObject()
{

}

gameObject::gameObject(Transform t) : transform(t)
{

}

void gameObject::setComponent(Component c)
{
    this->component = c;
}


