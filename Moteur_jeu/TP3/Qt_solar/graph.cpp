#include "graph.h"

Graph::Graph(gameObject o)
    : root(o)
{

}

Graph::~Graph(){

}

void Graph::update_transforms(gameObject o){
    gameObject cur = o;
    if(cur.children.size() <= 0){
        return;
    }

    for (unsigned int i=0; i < cur.children.size(); i++ ) {
        if(o.id != this->root.id){
            Transform updated_transform = cur.transform.combine_with(cur.parent->transform);
            cur.transform = updated_transform;
            cur.appyTransform(updated_transform);
        }
        update_transforms(cur.children[i]);
    }

}

void Graph::update_scene(){

    update_transforms(this->root);

}

void Graph::draw_elements(){

}
