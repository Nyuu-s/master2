#include "mesh.h"






unsigned int Mesh::getID(){
    return this->id;
}

VertexData* Mesh::VertextoArray(VertexData* arr, std::vector<VertexData> &tempV){

    for(unsigned int i  =0; i<this->vertices.size(); i++){
        arr[i].position = tempV[i].position;
        arr[i].texCoord = tempV[i].texCoord;
    }
    return arr;
}


unsigned short* Mesh::IndextoArray(unsigned short* arr){

    for(unsigned int i =0; i<this->indices.size(); i++){
        arr[i] = this->indices[i];
    }
    return arr;
}


Mesh::Mesh() : indexBuffer(QOpenGLBuffer::IndexBuffer){
    //this->id = id;
    this->indexNumber = 0;
    this->vertexNumber = 0;
    this->vertices = std::vector<VertexData>();
    this->indices = std::vector<GLushort>();

    vertexBuffer.create();
    indexBuffer.create();
}

Mesh::Mesh(std::vector<VertexData>& vertex, std::vector<GLushort>& indexes) : indexBuffer(QOpenGLBuffer::IndexBuffer)
{




    //this->id = id;
    this->indexNumber  = indexes.size();
    this->vertexNumber = vertex.size();

    this->indices =   std::vector<GLushort>(indexes);
    this->vertices =  std::vector<VertexData>(vertex);


    // Generate 2 VBOs
    vertexBuffer.create();
    indexBuffer.create();

}

Mesh::~Mesh(){
    vertexBuffer.destroy();
    indexBuffer.destroy();

}

Mesh::Mesh(std::vector<VertexData>& vertex) : indexBuffer(QOpenGLBuffer::IndexBuffer){


    this->vertexNumber = vertex.size();
    this->vertices.reserve(vertexNumber);
    this->indices = std::vector<GLushort>();
    this->vertices = vertex;

    vertexBuffer.create();
    indexBuffer.create();

}

void Mesh::loadOBJ(std::string filename, std::vector<QVector3D>& sphere ,std::vector<std::vector<unsigned int>>& face){
    OFFIO::open(filename, sphere, face, true);
}



void Mesh::Draw(QOpenGLShaderProgram& shaderProgram, std::vector<VertexData> &tempV){


      GeometryEngine geo = GeometryEngine();
      VertexData v[this->vertices.size()];
      GLushort arr[this->indices.size()];

      geo.drawGeometry(&shaderProgram, this->VertextoArray(v, tempV), this->IndextoArray(arr), this->vertexNumber, this->indexNumber);

}


void Mesh::printVertices(){
    for(unsigned int i=0; i < vertexNumber;i++){
        qDebug("%f, %f, %f", vertices[i].position.x(), vertices[i].position.y(),vertices[i].position.z());
    }
}
