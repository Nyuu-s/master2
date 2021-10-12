#include "transform.h"

Transform::Transform()
{

}

Transform::Transform(QMatrix4x4 m, QQuaternion r, QVector3D trans, float s)
    :
        matrix(m),
        scale(s),
        rotate(r),
        translate(trans)

{}


QVector3D Transform::applyToPoint(QVector3D p)
{
    return ( matrix * p + translate);
}

QVector3D Transform::applyToVector(QVector3D v)
{
    return ( matrix * v );
}
