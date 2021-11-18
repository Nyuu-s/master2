#ifndef GRAPH_H
#define GRAPH_H
#include"gameObject.h"
#include "camera.h"


class Graph
{
public:
    Graph(gameObject *go);
    ~Graph();
    gameObject *root;

    void update_scene();
    void draw_graph(QOpenGLShaderProgram& sp);

protected:
    void update_worldTransforms(gameObject* o);
    void update_localTransforms(gameObject* o);
    void draw_elements(gameObject& o, QOpenGLShaderProgram& shaderProgram);

};

#endif // GRAPH_H
