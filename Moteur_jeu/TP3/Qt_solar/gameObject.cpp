#include "gameObject.h"




gameObject::gameObject()
{

}

gameObject::gameObject(Transform t, int nChild = 3, int nComponent = 3) : transform(t)
{
    this->components.reserve(nComponent);
    this->children.reserve(nChild);
}

void gameObject::addComponent(Component c)
{
    this->components.push_back(c);
}

void gameObject::addChild(gameObject a){
    this->children.push_back(a);
}

void gameObject::setParent(gameObject a){
    this->parent = &a;
}

void gameObject::removeChild(gameObject c){
    for(unsigned int i =0; i<this->children.size(); i++){
        if(this->children[i].id == c.id){
            this->children.erase(this->children.begin()+i);
        }
    }
}

void gameObject::appyTransform(Transform transform)
{
    for(Component& component : this->components){

        if(instanceof<Mesh>(&component)){
            Mesh* mesh = dynamic_cast<Mesh*>(&component);
            for(auto vertex : mesh->vertices){
                transform.applyToPoint(vertex.position);
            }

        }
    }

}

void gameObject::removeComponent(Component c){
    for(unsigned int i =0; i<this->components.size(); i++){
        if(this->components[i].id == c.id){
            this->components.erase(this->components.begin()+i);
        }
    }
}

