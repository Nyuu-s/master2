#include "graph.h"




Graph::Graph(gameObject *obj)

{
    this->root = obj;
}

Graph::~Graph(){
    // TODO delete all gameObject from root to leaves
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
        obj->transform.matrix =  obj->parent->transform.matrix * obj->transform.getLocalModelMatrix() ;
    }

    for (unsigned int i=0; i < obj->children.size(); i++ )
    {
        //gameObject& cur = obj.children[i];
        update_worldTransforms(obj->children[i]);
    }

//    for(Component* comp : obj->components){
//        Mesh* mesh = dynamic_cast<Mesh*>(comp);
//        if (mesh != nullptr)
//            mesh->applyTransform(obj->world_transform);

//    }

}



// MODIFY TRANSFORM TO WORLD TRANSFORM A * B * C ...
void Graph::update_localTransforms(gameObject* obj){

    obj->transform = obj->transform.combine_with(obj->transform);

    for (unsigned int i=0; i < obj->children.size(); i++ ) {

        update_worldTransforms(obj->children[i]);
    }

    //obj.applyTransform();

}




void Graph::update_scene(){
    //first update locals matrix
    //update_localTransforms(this->root);

    //then update worlds matrix
    update_worldTransforms(this->root);



}

void Graph::draw_elements(gameObject &obj, QOpenGLShaderProgram& shaderProgram){

    shaderProgram.setUniformValue("transform",  obj.transform.matrix);
    obj.Draw(shaderProgram);

    for (auto &child : obj.children ) {
           draw_elements(*child, shaderProgram);
    }
}

// store shader program in graph class maybe ?

void Graph::draw_graph(QOpenGLShaderProgram& shaderProgram){
    draw_elements(*this->root, shaderProgram);



//    for(auto gameObj : root->children)
//        gameObj.Draw(shaderProgram);
}
