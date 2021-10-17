#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<transform.h>
#include"BasicIO.h"
#include"component.h"



class gameObject
{

public:

    Transform transform;
    gameObject();

    gameObject( Transform t);
    void setComponent(Component c);
    void addChild();

    std::vector<gameObject> children;
    gameObject* parent; // only one party is assumed for a gameObject

    Component component;


};

#endif // GAMEOBJECT_H
