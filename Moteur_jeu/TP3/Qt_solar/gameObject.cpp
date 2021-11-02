#include "gameObject.h"




gameObject::gameObject()
{

}

gameObject::gameObject(Transform t, int nChild , int nComponent , int go_id , std::string s ) : id(go_id), name(s), transform(t)
{
    this->components.reserve(nComponent);
    this->children.reserve(nChild);
}

void gameObject::addComponent(Component *c)
{
    this->components.push_back(c);
}

void gameObject::addChild(gameObject *a){
    this->children.push_back(*a);
}

void gameObject::setParent(gameObject& a){
    this->parent = &a;
}

void gameObject::removeChild(gameObject& c){
    for(unsigned int i =0; i<this->children.size(); i++){
        if(this->children[i].id == c.id){
            this->children.erase(this->children.begin()+i);
        }
    }
}

void gameObject::applyTransform()
{


        qDebug() << "r";
        for(Component *component : this->components){
            qDebug() << "transform scene...";
            Mesh* mesh = dynamic_cast<Mesh*>(component);

            if (mesh != nullptr){
                qDebug()<< "EST UN MESH";
                mesh->applyTransform(transform);
            }
            else
                qDebug()<<"PAS UN MESH";
        }


}

void gameObject::print(){
    qDebug("%s\n", this->name.c_str());
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
            mesh->Draw(shaderProgram);
        else
            qDebug()<<"Not a mesh impossible to draw --> implement a draw function for your object";

    }



}


