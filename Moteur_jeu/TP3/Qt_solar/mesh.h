#ifndef MESH_H
#define MESH_H

#include"BasicIO.h"
#include"geometryengine.h"
#include"componnent.h"
#include"transform.h"
#include"geometryengine.h"

class Mesh : public Component
{
public:
    unsigned int vertexNumber;
    unsigned int indexNumber;
    unsigned int id;

    std::vector<GLushort> indices;
    std::vector<VertexData> vertices;

    QOpenGLBuffer vertexBuffer;
    QOpenGLBuffer indexBuffer;


    Mesh();
    Mesh(std::vector<VertexData>& vertices, std::vector<GLushort>& indexes);
    Mesh(std::vector<VertexData>& vertices);
    ~Mesh();
    void Draw(QOpenGLShaderProgram& shaderProgram);
    static std::vector<QVector3D> loadOBJ(std::string filename);

    VertexData* VertextoArray(VertexData* arr);
    unsigned short* IndextoArray(unsigned short* arr);

    void applyTransform(Transform t);

    unsigned int getID();
    void printVertices();
};

#endif // MESH_H
