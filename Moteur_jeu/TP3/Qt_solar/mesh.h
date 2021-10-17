#ifndef MESH_H
#define MESH_H

#include"BasicIO.h"
#include"geometryengine.h"
#include"component.h"

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

    void printVertices();
};

#endif // MESH_H
