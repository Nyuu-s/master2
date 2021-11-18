#include "gameObject.h"




gameObject::gameObject()
{

}

gameObject::gameObject(Transform t, int nChild , int nComponent , int go_id , std::string s ) : id(go_id), name(s), transform(t)
{
    this->components.reserve(nComponent);
    this->children.reserve(nChild);
    this->parent = nullptr;
}

void gameObject::addComponent(Component *c)
{
    this->components.push_back(c);
}

void gameObject::setParent(gameObject* a){
    //si parent existe déja == changement de parent donc delete l'ancien child
    if(this->parent != nullptr){
        this->parent->removeChild(a);
    }


    if(a != nullptr){
        this->parent = a;
        this->parent->children.push_back(this);
    }
}

void gameObject::removeChild(gameObject* child){
    for(unsigned int i =0; i<this->children.size(); i++){
        if(this->children[i] == child){
            this->children.erase(this->children.begin()+i);
        }
    }
}

void gameObject::removeComponent(Component& c){
    for(unsigned int i =0; i<this->components.size(); i++){
        if(this->components[i]->id == c.id){
            this->components.erase(this->components.begin()+i);
        }
    }
}

void gameObject::Draw(QOpenGLShaderProgram& shaderProgram){
    for (auto component : this->components ) {

        Mesh* mesh = dynamic_cast<Mesh*>(component);
        if (mesh != nullptr)
        {
            mesh->Draw(shaderProgram, mesh->vertices);

        }
        else
            qDebug()<<"Not a mesh impossible to draw --> implement a draw function for your component";

    }



}


