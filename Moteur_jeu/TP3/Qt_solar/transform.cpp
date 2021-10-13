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

QVector4D Transform::apply(QVector4D p){
    QMatrix4x4 e = QMatrix4x4();

    QMatrix3x3 r = rotate.toRotationMatrix();
    e(0,0) = r(0,0);
    e(0,1) = r(0,1);
    e(0,2) = r(0,2);
    e(0,3) = 0.0f;

    e(1,0) = r(1,0);
    e(1,1) = r(1,1);
    e(1,2) = r(1,2);
    e(1,3) = 0;


    e(2,0) = r(2,0);
    e(2,1) = r(2,1);
    e(2,2) = r(2,2);
    e(2,3) = 0;


    e(3,0) = 0;
    e(3,1) = 0;
    e(3,2) = 0;
    e(3,3) = 1.0;


            //matrix * p ???
    return  scale * ( e * p) + translate;
}

Transform Transform::combine_with(Transform &t)
{
    // pertinent de faire matrix * t.matrix avec les autre argument?
    //peut etre une fonction decompose ?
    //fonction compose ?
    Transform res = Transform(matrix * t.matrix, rotate*t.rotate, translate + t.translate, scale * t.scale);
    return (res);
}
