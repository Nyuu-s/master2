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
** modifi
** tion, are permitted provided that the following conditions are
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
#define STB_IMAGE_IMPLEMENTATION

#include "mainwidget.h"

#include <QMouseEvent>

#include <math.h>

#include "mesh.h"
#include "gameObject.h"
#include "transform.h"
#include "graph.h"
#include<BasicIO.h>


MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    geometries(0),
    texture(0),
    angularSpeed(0)

{

    //initSphereGeometry(this->sphere);

}


void MainWidget::initGraph(int nb_mesh){
    this->meshList = (new std::vector<Mesh*>(nb_mesh));

    geometries = new GeometryEngine;
    QQuaternion q = QQuaternion::fromAxisAndAngle(1.f, 0.0f, 0.0f, 0.5);
    QQuaternion s = QQuaternion::fromAxisAndAngle(0.0f, 0.0f, 0.0f, 0.5);


    //GameObject( Transform T, child_number, component_number, ID, name)

    gameObject*  World  =   new gameObject(Transform(), 1, 1, 0, "world");
    Soleil =   new gameObject(Transform(q, QVector3D(0,0,0), 1),9,9, 1, "soleil"); // local transform par rapport au monde
    Terre  =   new gameObject(Transform(s, QVector3D(2,0,0), 1),1,1, 2,"Terre"); // local transform par rapport au soleil
//    gameObject Mercure = gameObject(Transform(QQuaternion(), QVector3D(), 1),1,1);
//    gameObject Venus = gameObject(Transform(QQuaternion(), QVector3D(), 1),1,1);
//    gameObject Mars = gameObject(Transform(QQuaternion(), QVector3D(), 1),1,1);





    std::vector<VertexData> v;
    std::vector<GLushort> index;

    this->initSphereGeometry(v, index);
    soleilMesh = new Mesh(v, index);
    soleilMesh ->id = 777;
    v.clear();
    index.clear();
    GeometryEngine::initCubeGeometry(64, 64, 1, 1,v, index);
    terreMesh = new Mesh(v, index);


// l'odre importe car addchild n'ajoute pas dans une liste de pointeur mais une liste d'obj

//    this->meshList->push_back(soleilMesh);
//    this->meshList->push_back(terreMesh);

    Terre->addComponent(terreMesh);
    Terre->setParent(Soleil); // use setParent and not addchild, store a pointer list and not object list

    Soleil->addComponent(soleilMesh);
    Soleil->setParent(World);

    graphScene = new Graph(World);



    Soleil->id = 777;




    //potentiel probleme : si tout les objet on le meme mesh apres une transformation tous les mesh sont mis a jour ?
    //maybe faire x instance de planet.
//    Soleil.addComponent(planet);
//    Mercure.addComponent(planet);
//    Venus.addComponent(planet);
//    Mars.addComponent(planet);
//    Terre.addComponent(planet);


//    Soleil.addChild(Mercure);
//    Soleil.addChild(Venus);
//    Soleil.addChild(Mars);
//    Soleil.addChild(Terre);

}

void MainWidget::initSphereGeometry(std::vector<VertexData>& points, std::vector<GLushort>& indices){
    std::string meshLocation = "../TP3/Qt_solar/sphere.obj";
    std::vector<QVector3D> sphere(Mesh::loadOBJ(meshLocation));
    points.reserve(sphere.size());
    indices.reserve(sphere.size());

    GLushort i = 0;
    for ( auto a : sphere ) {
        VertexData t = VertexData();
        t.position = a;
        //qDebug("%f, %f, %f hdshv", a.x(), a.y(), a.z());
       // t.texCoord = ??
        points.push_back(t);
        indices.push_back(i++);
    }

}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete soleilMesh;
    delete terreMesh;
    for(auto ptr : *meshList){
        delete ptr;
    }
    delete meshList;
    delete texture;
    delete heightmap;
    delete snow;
    delete rock;
    delete geometries;
    delete graphScene;
    doneCurrent();
}

//! [0]
void MainWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}
//! [0]

//! [1]
void MainWidget::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Request an update
        update();
    }





}
//! [1]

void MainWidget::keyPressEvent(QKeyEvent *event)
{



    switch (event->key()) {
        case Qt::Key_Z: /* haut */
            projection.translate(0.0, -1.0, 0.0);
            break;
        case Qt::Key_Q: /* gauche */;
            projection.translate(1.0, 0.0, 0.0);
            break;
        case Qt::Key_D: /*droite */
            projection.translate(-1.0, 0.0, 0.0);
          break;
        case Qt::Key_S: /* bas */
            projection.translate(0.0, 1.0, 0.0);
            break;
        case Qt::Key_A: /* descendre */
            projection.translate(0.0, 0.0, 1.0);
            break;
        case Qt::Key_E: /* monter */
            projection.translate(0.0, 0.0, -1.0);
            break;





    }

    //projection.translate(0.0, 0.0, -1.0) ;
      update();

    // Save mouse press position
  //  mousePressPosition = QVector2D(e->localPos());
}

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();

//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
   // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//! [2]



   // geometries = new GeometryEngine;

    initGraph(2); // k = nb meshs

    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);
}

//! [3]
void MainWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}
//! [3]

//! [4]
void MainWidget::initTextures()
{
    // Load cube.png image
    texture = new QOpenGLTexture(QImage(":/grass.png").mirrored());
    rock = new QOpenGLTexture(QImage(":/rock.png").mirrored());
    snow = new QOpenGLTexture(QImage(":/snowrocks.png").mirrored());
    heightmap = new QOpenGLTexture(QImage(":/Heightmap_Rocky.png").mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    rock->setMinificationFilter(QOpenGLTexture::Nearest);
    snow->setMinificationFilter(QOpenGLTexture::Nearest);
    //heightmap->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    rock->setMagnificationFilter(QOpenGLTexture::Linear);
    snow->setMagnificationFilter(QOpenGLTexture::Linear);
   // heightmap->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
    rock->setWrapMode(QOpenGLTexture::Repeat);
    snow->setWrapMode(QOpenGLTexture::Repeat);
    heightmap->setWrapMode(QOpenGLTexture::Repeat);
}
//! [4]

//! [5]
void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 1.0, zFar = 500.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}
//! [5]

void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




    texture->bind(0);
    heightmap->bind(1);
    rock->bind(2);
    snow->bind(3);

//! [6]
    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -10.0);
    matrix.rotate(rotation);

    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix", projection * matrix);
//! [6]
//!
//!
//! ../TP3/Qt_solar/sphere.obj


    // Use texture unit 0 which contains cube.png
    program.setUniformValue("texture", 0);
    program.setUniformValue("rock", 2);
    program.setUniformValue("snow", 3);
    program.setUniformValue("heightmap", 1);
   // qDebug() << graphScene->root->id << " " << graphScene->root->name.c_str();
    Soleil->transform.rotate *= QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, 0.5);
    //Terre->transform.rotate *= QQuaternion::fromAxisAndAngle(0.0f, 0.0f, 1.0f, 0.5);
    graphScene->update_scene();
    graphScene->draw_graph(program);

    //graphScene->update_scene();
    update();

    // Draw plane geometry

    //geometries->drawCubeGeometry(&program);

   // geometries->drawSphereGeometry(&program);
}
