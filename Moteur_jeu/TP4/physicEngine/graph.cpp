#include "graph.h"



Graph::Graph(gameObject *obj)

{
    this->root = obj;
}

Graph::~Graph(){
    // TODO delete all gameObject from root to leaves
    delete root;
}


// MODIFY TRANSFORM TO WORLD TRANSFORM A * B * C ...
void Graph::update_worldTransforms(gameObject* obj)
{

    if(this->root->id == obj->id)
    {
        obj->transform.matrix = obj->transform.getLocalModelMatrix();
    }
    else
    {
        Camera* cam = dynamic_cast<Camera*>(obj);
        obj->transform.matrix =  obj->parent->transform.matrix * obj->transform.getLocalModelMatrix() ;
        if(cam != nullptr){
            cam->transform.inverseWorld();

        }
    }

    for (unsigned int i=0; i < obj->children.size(); i++ )
    {
        update_worldTransforms(obj->children[i]);
    }


}


void Graph::update_scene(){

    update_worldTransforms(this->root);
}

void Graph::draw_elements(gameObject &obj, QOpenGLShaderProgram& shaderProgram){

    shaderProgram.setUniformValue("transform",  obj.transform.matrix);
    obj.Draw(shaderProgram);

    for (auto &child : obj.children ) {
           draw_elements(*child, shaderProgram);
    }
}



void Graph::draw_graph(QOpenGLShaderProgram& shaderProgram){
    draw_elements(*this->root, shaderProgram);
}
