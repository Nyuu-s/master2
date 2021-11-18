#ifndef MESH_H
#define MESH_H

#include"BasicIO.hpp"
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
    void Draw(QOpenGLShaderProgram& shaderProgram, std::vector<VertexData> &tempV );

    static void loadOBJ(std::string filename, std::vector<QVector3D>& sphere, std::vector<std::vector<unsigned int>>& face);

    VertexData* VertextoArray(VertexData* arr, std::vector<VertexData> &tempV);
    unsigned short* IndextoArray(unsigned short* arr);

    void applyTransform(Transform t, std::vector<VertexData> &v);

    unsigned int getID();
    void printVertices();
private:
    using Component::applyTransform;
};

#endif // MESH_H
