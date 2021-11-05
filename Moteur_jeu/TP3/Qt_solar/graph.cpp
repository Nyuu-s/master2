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
        obj->world_transform = obj->transform;
    }
    else
    {
        qDebug() << "changement de world_transform pour " << obj->name.c_str() << "\n";

        obj->world_transform =  obj->parent->world_transform * obj->transform; //obj->transform.combine_with(obj->parent->world_transform); // multiply current local with parents's world transform
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

    obj.Draw(shaderProgram);

    for (auto game_object : obj.children ) {
           draw_elements(*game_object, shaderProgram);
    }
}

// store shader program in graph class maybe ?

void Graph::draw_graph(QOpenGLShaderProgram& shaderProgram){
    draw_elements(*this->root, shaderProgram);

//    for(auto gameObj : root->children)
//        gameObj.Draw(shaderProgram);
}
