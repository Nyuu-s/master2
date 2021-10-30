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

    std::vector<gameObject> children;
    gameObject* parent; // only one party is assumed for a gameObject

    std::vector<Component*> components;

    Transform transform;
    gameObject();
    gameObject( Transform t, int n, int m, std::string s);

    void print();
    void copy(const gameObject& src, gameObject& dst);
    void addComponent(Component *c);
    void addChild(gameObject *a);
    void setParent(gameObject& a);
    void removeChild(gameObject& c);
    void removeComponent(Component& c);
    void applyTransform(Transform& transform);
    void Draw(QOpenGLShaderProgram& shaderProgram);
    template<typename Base, typename T>
    inline bool instanceof(const T*) {
       return std::is_base_of<Base, T>::value;
    }





};

#endif // GAMEOBJECT_H
