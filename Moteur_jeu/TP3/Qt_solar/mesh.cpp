#include "mesh.h"


Mesh::Mesh(){
    this->id = ids;
    this->indexNumber = 0;
    this->vertexNumber = 0;
    this->vertices = new VertexData[1];
    this->indices = new GLushort[1];


}

Mesh::getID(){
    return this->id;
}
Mesh::Mesh(VertexData& vertices, GLushort indexes[], unsigned int vertexCount, unsigned int indexCount) {
    this->id = ids;
    this->indexNumber = indexCount;
    this->vertexNumber = vertexCount;
    this->vertices = new VertexData[vertexNumber];
    this->indices = new GLushort[indexNumber];
    *this->vertices = vertices;
    this->indices = indexes;

}

void Mesh::loadOBJ(std::string filename){
    std::vector<QVector3D>  points;
    //std::vector< std::vector<int>> faces;
    OBJIO::open(filename, points);

    this->vertexNumber = points.size();
    this->vertices = new VertexData[vertexNumber];

    for(unsigned int i=0; i<points.size();i++){
        vertices[i].position = points[i];
    }
}


void Mesh::printVertices(){
    for(unsigned int i=0; i < vertexNumber;i++){
        qDebug("%f, %f, %f", vertices[i].position.x(), vertices[i].position.y(),vertices[i].position.z());
    }
}
