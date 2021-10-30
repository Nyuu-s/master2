#include "graph.h"




Graph::Graph(gameObject *obj)

{
    this->root = obj;
}

Graph::~Graph(){

}

// MODIFY TRANSFORM TO WORLD TRANSFORM A * B * C ...
//void Graph::update_transforms(gameObject& o){
//    gameObject cur = o;

//    if(cur.children.size() <= 0){
//        Transform updated_transform = cur.transform.combine_with(cur.parent->transform); // conserver une matrice locale et world ? ou juste world ?
//        cur.transform = updated_transform;

//        return;
//    }

//    for (unsigned int i=0; i < cur.children.size(); i++ ) {
//        qDebug() << cur.id << " != " << this->root->id << " " <<(cur.id != this->root->id) ;
//        if(cur.id != this->root->id){
//            Transform updated_transform = cur.transform.combine_with(cur.parent->transform); // conserver une matrice locale et world ? ou juste world ?
//            cur.transform = updated_transform;
//           // cur.applyTransform(updated_transform);
//        }
//        update_transforms(cur.children[i]);
//    }

//}

void Graph::update_transforms2(gameObject& obj){

    obj.applyTransform(obj.children[0].transform);

}

void Graph::update_scene(){
    qDebug() << "update scene...";
    update_transforms2(*this->root);


}


void Graph::draw_elements(QOpenGLShaderProgram& shaderProgram){

    root->children[0].Draw(shaderProgram);
}
