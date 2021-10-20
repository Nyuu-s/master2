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
    std::vector<VertexData> vertices;


    Mesh();
    Mesh(std::vector<VertexData>& vertices, GLushort indexes[], unsigned int vertexCount, unsigned int indexCount);
    Mesh(std::vector<VertexData>& vertices,  unsigned int vertexCount);
    static std::vector<QVector3D> loadOBJ(std::string filename);

    unsigned int getID();
    void printVertices();
};

#endif // MESH_H
