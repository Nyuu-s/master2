#include "mesh.h"


Mesh::Mesh(){
    //this->id = id;
    this->indexNumber = 0;
    this->vertexNumber = 0;
    this->vertices = std::vector<VertexData>();
    this->indices = new GLushort[1];


}

unsigned int Mesh::getID(){
    return this->id;
}

VertexData* Mesh::toArray(VertexData* arr){

    for(unsigned int i =0; i<this->vertices.size(); i++){
        arr[i].position = this->vertices[i].position;
        arr[i].texCoord = this->vertices[i].texCoord;
    }
    return arr;
}

Mesh::Mesh(std::vector<VertexData>& v, GLushort indexes[], unsigned int vertexCount, unsigned int indexCount) {
    //this->id = id;
    this->indexNumber = indexCount;
    this->vertexNumber = vertexCount;
    this->vertices.reserve(vertexNumber);
    this->indices = new GLushort[indexNumber];
    this->vertices = v;
    this->indices = indexes;

}

Mesh::Mesh(std::vector<VertexData>& v, unsigned int vertexCount) {
    //this->id = id;

    this->vertexNumber = vertexCount;
    this->vertices.reserve(vertexNumber);
    this->indices = new GLushort[indexNumber];
    this->vertices = v;


}

    std::vector<QVector3D> Mesh::loadOBJ(std::string filename){
    std::vector<QVector3D>  points;
    //std::vector< std::vector<int>> faces;
    OBJIO::open(filename, points);

    return points;

}


void Mesh::printVertices(){
    for(unsigned int i=0; i < vertexNumber;i++){
        qDebug("%f, %f, %f", vertices[i].position.x(), vertices[i].position.y(),vertices[i].position.z());
    }
}
