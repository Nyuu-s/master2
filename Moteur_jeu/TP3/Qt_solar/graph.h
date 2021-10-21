#ifndef GRAPH_H
#define GRAPH_H
#include"gameObject.h"


class Graph
{
public:
    Graph(gameObject);
    ~Graph();
    gameObject root;

    void update_scene();
    void draw_elements();

private:
    void update_transforms(gameObject o);
};

#endif // GRAPH_H
