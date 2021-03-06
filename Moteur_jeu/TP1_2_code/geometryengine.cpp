/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "geometryengine.h"

#include <iostream>

#include <QVector2D>
#include <QVector3D>
#include <cstdlib>
#include <ctime>
#include<QImage>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//! [0]
GeometryEngine::GeometryEngine()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    //int width, height, nrChannels = 0;
   // unsigned char *data = stbi_load(":/Heightmap_Mountain.png", &width, &height, &nrChannels, STBI_rgb_alpha);
    QImage data;
    data.load(":/heightmap-1024x1024.png");



    // Initializes cube geometry and transfers it to VBOs
    initCubeGeometry(64, 64, 3, 3, data);



}

GeometryEngine::~GeometryEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}
//! [0]
//!



void GeometryEngine::initCubeGeometry(int nH,int nW, int boardSizeX,int  boardSizeY, QImage &heightmap)
{




//    float  yStep = (1.0 - (-1.0) / float(nH-1));
//    float  xStep = (1.0 - (-1.0) / float(nW-1));

//    // For cube we would need only 8 vertices but we have to
//    // duplicate vertex for each face because texture coordinate
//    // is different.
//    // Hence 4 vertices per face and 6 faces vertices = 24 vertices
//    unsigned int vertexNumber = nH*nW ;
//    VertexData vertices[vertexNumber];

//    for (int y; y<nH ; y++ ) {
//        for (int x; x<nW ;x++ ) {
//            vertices[y*nH+x].position = QVector3D(-1.0+xStep*y, -1.0+yStep*x, 0.0);
//        }

//    }

//    // Indices for drawing cube faces using triangle strips.
//    // Triangle strips can be connected by duplicating indices
//    // between the strips. If connecting strips have opposite
//    // vertex order then last index of the first strip and first
//    // index of the second strip needs to be duplicated. If
//    // connecting strips have same vertex order then only last
//    // index of the first strip needs to be duplicated.
//    unsigned int indexCount = nW*nH+nH*(nW-2)+2*(nW-2)+2;
//   GLushort indices[indexCount];
//   int e = 0;
//    for (int y; y<nH-1 ; y++ ) {
//        for (int x; x<nW ;x++ ) {
//            indices[2*y+y*(nH*2)+x*2] = y*nH+x;
//            indices[2*y+y*(nH*2)+x*2+1] = (y+1)*nH+x;
//            indices[2*y+y*(nH*2)+nH*2]=(y+1)*nH+nH-1;
//            indices[2*y+y*(nH*2)+nH*2+1]=(y+1)*nH;
//        }

  //  }
    float plan_xmax = boardSizeX;   //---
    float plan_xmin = -boardSizeX;  // taille r??el du plan
    float plan_ymax = boardSizeY;   //
    float plan_ymin = -boardSizeY;  //--
    float tex_xStep=2/(float)(nW-1);    // interval pour les textures
    float tex_yStep=2/(float)(nH-1);    //--

    float xStep=(plan_xmax-plan_xmin)/(float)(nW-1); // interval pour la g??om??trie (triangles)
    float yStep=(plan_ymax-plan_ymin)/(float)(nH-1); //--
    srand (static_cast <unsigned> (time(0)));

    int k=0;


    //vertex buffer
    unsigned int vertexNumber = nH*nW;
    VertexData vertices[vertexNumber];
    for(int i=0; i<nH; i++){
         for(int j=0;j<nW; j++){
             //QRgb test = heightmap.pixel(  j, i);  

          //   qDebug("%d", qGray(test) );
          //  float r = static_cast <float>  (qGray(test))/ 255.0; r est de base le z qu'il demande de denifir de maniere random quelque part
           // qDebug("%f", r );
             vertices[k++]= {QVector3D(                     // ajout des sommets et coord de texture pour la subdivision
                                    plan_xmin + xStep * i,
                                    plan_ymin + yStep * j,
                                    0.0),
                             QVector2D(
                                    (tex_xStep*i)/2,
                                    (tex_yStep*j)/2
                                     )
                            };

        }
    }



    unsigned int indexCount = nW*(nH-1)*2 + 2*(nH-1); // calcul du nombre d'index, utilisant le triangle strip des sommet vont se repeter il ne fau pas les compter 40 fois
    GLushort indices[indexCount];

    //index buffer
    int e=0;
    for(int i=0; i<nH-1; i++){
         for(int j=0;j<nW; j++){
             //stripe 
                 indices[e++] = i*nH+j;
                 indices[e++] = (i+1)*nH+j;

             }
            //end line stripe
             indices[e++]=(i+1)*nH+nH-1;
             indices[e++]=(i+1)*nH;
         }


//! [1]
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, vertexNumber * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices,  indexCount* sizeof(GLushort));
//! [1]
}

//! [2]
void GeometryEngine::drawCubeGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, indexBuf.size()/2, GL_UNSIGNED_SHORT, 0); //Careful update indicesNumber when creating new geometry
}
//! [2]
