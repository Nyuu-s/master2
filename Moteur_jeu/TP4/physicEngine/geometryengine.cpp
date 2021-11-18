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



#include <iostream>

#include<BasicIO.h>
#include <QVector2D>
#include <QVector3D>
#include <cstdlib>
#include <ctime>
#include<QImage>
#include <vector>
#include <string>
#include "transform.h"
#include <iostream>
#include"mesh.h"
#include "gameObject.h"
#include <QOpenGLWidget>

#define STB_IMAGE_IMPLEMENTATION


//! [0]
GeometryEngine::GeometryEngine()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{

    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();



    // Initializes cube geometry and transfers it to VBOs
   // initCubeGeometry(64, 64, 1, 1);
    //initSphereGeometry();




}

GeometryEngine::~GeometryEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}
//! [0]
//!


void initSphereGeometry(std::vector<VertexData>& points, std::vector<GLushort>& indices){


}


void GeometryEngine::initCubeGeometry(int nH,int nW, int boardSizeX,int  boardSizeY, std::vector<VertexData>& points, std::vector<GLushort>& indices)
{






    float plan_xmax = boardSizeX;
    float plan_xmin = -boardSizeX;
    float plan_ymax = boardSizeY;
    float plan_ymin = -boardSizeY;
    float tex_xStep=2/(float)(nW-1);
    float tex_yStep=2/(float)(nH-1);

    float xStep=(plan_xmax-plan_xmin)/(float)(nW-1);
    float yStep=(plan_ymax-plan_ymin)/(float)(nH-1);
    srand (static_cast <unsigned> (time(0)));




//########################################################### PLANE HEIGHT MAP #######################################""

    unsigned int vertexNumber = nH*nW;
    points.reserve(vertexNumber);
    for(int i=0; i<nH; i++){
         for(int j=0;j<nW; j++){
             points.push_back( {QVector3D(
                                    plan_xmin + xStep * i,
                                    plan_ymin + yStep * j,
                                    0.0),
                             QVector2D(
                                    (tex_xStep*i)/2,
                                    (tex_yStep*j)/2
                                     )
                            });

        }
    }




    unsigned int indexCount = nW*(nH-1)*2 + 2*(nH-1);
    indices.reserve(indexCount);
    for(int i=0; i<nH-1; i++){
         for(int j=0;j<nW; j++){
             //stripe
                 indices.push_back(i*nH+j);
                 indices.push_back((i+1)*nH+j);

             }
            //end line stripe
             indices.push_back((i+1)*nH+nH-1);
             indices.push_back((i+1)*nH);
         }

}

//! [2]
void GeometryEngine::drawGeometry(QOpenGLShaderProgram *program, VertexData* vertices, GLushort* indices, int vertexNumber, int indexCount)
{

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, vertexNumber * sizeof(VertexData));

//   //  Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices,  indexCount* sizeof(GLushort));
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


void GeometryEngine::drawSphereGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    //indexBuf.bind();

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
    glDrawElements(GL_TRIANGLES, indexBuf.size(), GL_UNSIGNED_SHORT, 0); //Careful update indicesNumber when creating new geometry
}
//! [2]
