#include "gameObject.h"

gameObject::gameObject()
{

}

gameObject::gameObject(QMatrix4x4 m, QQuaternion r, QVector3D t)
{
    transform = Transform(m, r, t);
}

