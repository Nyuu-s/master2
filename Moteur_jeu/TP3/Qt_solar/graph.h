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
    void draw_graph(QOpenGLShaderProgram& sp);

protected:
    void update_transforms(gameObject& o);
    void draw_elements(gameObject& o, QOpenGLShaderProgram& shaderProgram);

};

#endif // GRAPH_H
