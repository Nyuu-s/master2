#include "mesh.h"






unsigned int Mesh::getID(){
    return this->id;
}

VertexData* Mesh::VertextoArray(VertexData* arr){

    for(unsigned int i =0; i<this->vertices.size(); i++){
        arr[i].position = this->vertices[i].position;
        arr[i].texCoord = this->vertices[i].texCoord;
    }
    return arr;
}


unsigned int* Mesh::IndextoArray(unsigned int* arr){

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
    this->indexNumber = indexes.size();
    this->vertexNumber = vertex.size();
    std::vector<GLushort> tempInd = *(new std::vector<GLushort>(indexes));
    this->indices = tempInd;
    this->vertices = *(new std::vector<VertexData>(vertex));


    // Generate 2 VBOs
    vertexBuffer.create();
    indexBuffer.create();

}

Mesh::~Mesh(){
    vertexBuffer.destroy();
    indexBuffer.destroy();

}

Mesh::Mesh(std::vector<VertexData>& vertex) : indexBuffer(QOpenGLBuffer::IndexBuffer){
    //this->id = id;

    this->vertexNumber = vertex.size();
    this->vertices.reserve(vertexNumber);
    this->indices = std::vector<GLushort>();
    this->vertices = vertex;

    vertexBuffer.create();
    indexBuffer.create();


}

std::vector<QVector3D> Mesh::loadOBJ(std::string filename){
     std::vector<QVector3D>  points;
    //std::vector< std::vector<int>> faces;
    OBJIO::open(filename, points);

    return points;

}


void Mesh::Draw(QOpenGLShaderProgram& shaderProgram){

    VertexData vertices_arr[vertices.size()];
    this->VertextoArray(vertices_arr);

    VertexData indices_arr[vertices.size()];
    this->VertextoArray(indices_arr);
    qDebug() << indices_arr <<" test";

    vertexBuffer.bind() ;
    vertexBuffer.allocate(vertices_arr, vertexNumber * sizeof(VertexData));

    indexBuffer.bind();
    indexBuffer.allocate(indices_arr,  indexBuffer.size() * sizeof(GLushort));





    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = shaderProgram.attributeLocation("a_position");
    shaderProgram.enableAttributeArray(vertexLocation);
    shaderProgram.setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = shaderProgram.attributeLocation("a_texcoord");
    shaderProgram.enableAttributeArray(texcoordLocation);
    shaderProgram.setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, indexBuffer.size()/2, GL_UNSIGNED_SHORT, 0); //Careful update indicesNumber when creating new geometry
}


void Mesh::printVertices(){
    for(unsigned int i=0; i < vertexNumber;i++){
        qDebug("%f, %f, %f", vertices[i].position.x(), vertices[i].position.y(),vertices[i].position.z());
    }
}
