#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<transform.h>
class gameObject
{

public:
    Transform transform;
    gameObject();

    gameObject(QMatrix4x4 m, QQuaternion r, QVector3D t, float s);
};

#endif // GAMEOBJECT_H
