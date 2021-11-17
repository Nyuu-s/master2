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
    //this->id = id;

    this->vertexNumber = vertex.size();
    this->vertices.reserve(vertexNumber);
    this->indices = std::vector<GLushort>();
    this->vertices = vertex;

    vertexBuffer.create();
    indexBuffer.create();

}

void Mesh::loadOBJ(std::string filename, std::vector<QVector3D>& sphere ,std::vector<std::vector<unsigned int>>& face){
    //std::vector<QVector3D>  points;
    //std::vector< std::vector<int>> faces;
    OFFIO::open(filename, sphere, face, true);

   // return points;

}

void Mesh::applyTransform(Transform t, std::vector<VertexData> &tempV){
    int i=0;

    for(auto vertex : this->vertices){
        //this->vertices[i].position = this->vertices[i].position + t.translate;
        tempV[i].position = t.applyToPoint(vertex.position);
        tempV[i].texCoord = vertex.texCoord;
        i++;

    }
}

void Mesh::Draw(QOpenGLShaderProgram& shaderProgram, std::vector<VertexData> &tempV){


      GeometryEngine geo = GeometryEngine();
      VertexData v[this->vertices.size()];
      GLushort arr[this->indices.size()];

      geo.drawCubeGeometry(&shaderProgram, this->VertextoArray(v, tempV), this->IndextoArray(arr), this->vertexNumber, this->indexNumber);

//    VertexData vertices_arr[vertices.size()];
//    this->VertextoArray(vertices_arr);

//    VertexData indices_arr[vertices.size()];
//    this->VertextoArray(indices_arr);
//    qDebug() << indices_arr <<" test";

//    vertexBuffer.bind() ;
//    vertexBuffer.allocate(vertices_arr, vertexNumber * sizeof(VertexData));

//    indexBuffer.bind();
//    indexBuffer.allocate(indices_arr,  indexBuffer.size() * sizeof(GLushort));





//    // Offset for position
//    quintptr offset = 0;

//    // Tell OpenGL programmable pipeline how to locate vertex position data
//    int vertexLocation = shaderProgram.attributeLocation("a_position");
//    shaderProgram.enableAttributeArray(vertexLocation);
//    shaderProgram.setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

//    // Offset for texture coordinate
//    offset += sizeof(QVector3D);

//    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
//    int texcoordLocation = shaderProgram.attributeLocation("a_texcoord");
//    shaderProgram.enableAttributeArray(texcoordLocation);
//    shaderProgram.setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

//    // Draw cube geometry using indices from VBO 1
  //  glDrawElements(GL_TRIANGLE_STRIP, indexBuffer.size()/2, GL_UNSIGNED_SHORT, 0); //Careful update indicesNumber when creating new geometry
}


void Mesh::printVertices(){
    for(unsigned int i=0; i < vertexNumber;i++){
        qDebug("%f, %f, %f", vertices[i].position.x(), vertices[i].position.y(),vertices[i].position.z());
    }
}
