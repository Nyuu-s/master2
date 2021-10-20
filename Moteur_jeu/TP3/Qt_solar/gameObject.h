#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<transform.h>
#include"BasicIO.h"

#include"componnent.h"


class gameObject
{

public:


    unsigned int id;
    std::string name;

    Transform transform;
    gameObject();

    gameObject( Transform t, int n, int m);
    void addComponent(Component c);
    void addChild(gameObject a);
    void setParent(gameObject a);
    void removeChild(gameObject c);
    void removeComponent(Component c);

    std::vector<gameObject> children;
    gameObject* parent; // only one party is assumed for a gameObject

    std::vector<Component> components;




};

#endif // GAMEOBJECT_H
