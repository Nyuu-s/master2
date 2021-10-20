#ifndef MESH_H
#define MESH_H

#include"BasicIO.h"
#include"geometryengine.h"
#include"componnent.h"

class Mesh : public Component
{
public:
    unsigned int vertexNumber;
    unsigned int indexNumber;
    unsigned int id;

    GLushort* indices;
    VertexData* vertices;


    Mesh();
    Mesh(VertexData& vertices, GLushort indexes[], unsigned int vertexCount, unsigned int indexCount);
    void loadOBJ(std::string filename);

    unsigned int getID();
    void printVertices();
};

#endif // MESH_H
