#ifndef GRAPH_H
#define GRAPH_H
#include"gameObject.h"


class Graph
{
public:
    Graph(gameObject *go);
    ~Graph();
    gameObject *root;

    void update_scene();
    void draw_elements(QOpenGLShaderProgram& sp);

protected:
    void update_transforms(gameObject& o);
    void update_transforms2(gameObject& o);
};

#endif // GRAPH_H
