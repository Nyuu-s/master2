#include "graph.h"




Graph::Graph(gameObject *obj)

{
    this->root = obj;
}

Graph::~Graph(){
    // TODO delete all gameObject from root to leaves
}


// MODIFY TRANSFORM TO WORLD TRANSFORM A * B * C ...
void Graph::update_transforms(gameObject& obj){


    if(obj.children.size() <= 0){
//        Transform updated_transform = obj.transform.combine_with(obj.parent->transform); // conserver une matrice locale et world ? ou juste world ?
//        obj.transform = updated_transform;
        obj.applyTransform();
        return;
    }

    for (unsigned int i=0; i < obj.children.size(); i++ ) {
        gameObject *cur = &obj.children[i];
        if(cur->id != this->root->id){
            Transform updated_transform = cur->transform.combine_with(cur->parent->transform); // conserver une matrice locale et world ? ou juste world ?
            cur->transform = updated_transform;

        }
        update_transforms(*cur);
    }

    obj.applyTransform();

}




void Graph::update_scene(){
    //first update locals transforms


    //then update
    update_transforms(*this->root);



}

void Graph::draw_elements(gameObject &obj, QOpenGLShaderProgram& shaderProgram){
    if(obj.children.size() <= 0){
        obj.Draw(shaderProgram);
        return;
    }

    for (auto &game_object : obj.children ) {
           game_object.Draw(shaderProgram);
           draw_elements(game_object, shaderProgram);
    }
}

// store shader program in graph class maybe ?

void Graph::draw_graph(QOpenGLShaderProgram& shaderProgram){
    draw_elements(*this->root, shaderProgram);

//    for(auto gameObj : root->children)
//        gameObj.Draw(shaderProgram);
}
