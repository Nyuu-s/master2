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

//void gameObject::addChild(gameObject *a){
//    this->children.push_back(*a);
//}

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

void gameObject::applyTransform(Transform &t)
{
        for(Component *component : this->components){
            qDebug() << "transform scene...";
            Mesh* mesh = dynamic_cast<Mesh*>(component);

            if (mesh != nullptr){
                qDebug()<< "EST UN MESH";
                mesh->applyTransform(t, mesh->vertices);
            }
            else
                qDebug()<<"PAS UN MESH";
        }

        for(auto &obj : children){
            obj->applyTransform(t);
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
       // mesh->applyTransform(transform, mesh->vertices);


        if (mesh != nullptr)
        {
            //std::vector<VertexData> tempV = std::vector<VertexData>(mesh->vertices);
           // mesh->applyTransform(transform, mesh->vertices);
           // QQuaternion q = QQuaternion::fromAxisAndAngle   (0.f, 1.0f, 0.0f, 0.5);
           // mesh->applyTransform(Transform(q, QVector3D(0,0,0), 1), mesh->vertices);
            //mesh->applyTransform(world_transform, tempV);


           // qDebug() << this->name.c_str() << tempV[0].position[0] << " " << tempV[0].position[1] << tempV[0].position[2];

            mesh->Draw(shaderProgram, mesh->vertices);

        }
        else
            qDebug()<<"Not a mesh impossible to draw --> implement a draw function for your object";

    }



}


