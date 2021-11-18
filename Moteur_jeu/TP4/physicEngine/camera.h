#ifndef CAMERA_H
#define CAMERA_H

#include"transform.h"
#include "gameObject.h"

class Camera : public gameObject
{
public: 
    Camera();
    ~Camera();
    void isUsless(){};
    QVector3D up;
    QVector3D position;

};

#endif // CAMERA_H
