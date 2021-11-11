#include "transform.h"

Transform::Transform()
{
    matrix = QMatrix4x4();
    matrix.setToIdentity();
    rotate = QQuaternion();
    scale = 1;
    translate = QVector3D();
}

Transform::Transform( QQuaternion r, QVector3D trans, float s)
    :
        scale(s),
        rotate(r),
        translate(trans)

{
    matrix = (QMatrix4x4(rotate.toRotationMatrix()) * scale);
    matrix(0,3) = translate.x();
    matrix(1,3) = translate.y();
    matrix(2,3) = translate.z();
    matrix(3,3) = 1;

}





QVector3D Transform::applyToPoint(QVector3D p)
{
    return ( rotate.rotatedVector(p) * scale) + translate   ;
}

QVector3D Transform::applyToVector(QVector3D v)
{
    return ( rotate.rotatedVector(v) * scale );
}

QVector3D Transform::applyToVersor(QVector3D v)
{
    return ( rotate.rotatedVector(v) );
}

QVector4D Transform::apply(QVector4D p){

//    QMatrix4x4 e = QMatrix4x4(rotate.toRotationMatrix());

//    e(3,0) = 0;
//    e(3,1) = 0;
//    e(3,2) = 0;
//    e(3,3) = 1.0;

    QVector3D t = QVector3D(p.x(), p.y(), p.z());
    t = (rotate.rotatedVector(t) + translate )* scale;
            //???scale * ( e * p) + translate
    return QVector4D(t.x(), t.y(), t.z(), p.w());
}

Transform Transform::combine_with(Transform &t)
{


    Transform res = Transform( rotate * t.rotate,  translate + t.translate,  scale * t.scale);
    return (res);
}


Transform Transform::inverse(){
    Transform res = Transform( rotate.inverted(), -translate, 1/scale);
    return res;
}


