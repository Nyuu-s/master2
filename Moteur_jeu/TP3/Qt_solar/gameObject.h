#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<transform.h>
#include"BasicIO.h"
#include "mesh.h"
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
    void appyTransform(Transform transform);

    std::vector<gameObject> children;
    gameObject* parent; // only one party is assumed for a gameObject

    std::vector<Component> components;

    template<typename Base, typename T> bool instanceof(const T*) {
       return std::is_base_of<Base, T>::value;
    }




};

#endif // GAMEOBJECT_H
