#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<transform.h>


template<typename T, int N>
struct Component
{
    std::vector<T> entities;
    Component()
    {
        entities.reserve(N);
    }

    void add(T ent)
    {
        entities.push_back(ent);
    }


class gameObject
{

public:

    Transform transform;
    gameObject();

    gameObject( Transform t);

    std::vector<gameObject> children;
    gameObject* parent; // only one party is assumed for a gameObject

    Component component;


};

#endif // GAMEOBJECT_H
