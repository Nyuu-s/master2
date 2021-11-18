#include "transform.h"

Transform::Transform()
{
    matrix = QMatrix4x4();
    rotate = QQuaternion();
    scale = 1;
    position = QVector3D();
}

Transform::Transform( QQuaternion r, QVector3D trans, float s)
    :
        scale(s),
        rotate(r),
        position(trans)

{
//    matrix = (QMatrix4x4(rotate.toRotationMatrix()) * scale );
//    matrix(0,3) = position.x();
//    matrix(1,3) = position.y();
//    matrix(2,3) = position.z();
//    matrix(3,3) = 1;

}

QMatrix4x4 Transform::getLocalModelMatrix(){

    QMatrix4x4 modelMatrix = QMatrix4x4(rotate.toRotationMatrix() * scale);
    modelMatrix(0,3) = position.x();
    modelMatrix(1,3) = position.y();
    modelMatrix(2,3) = position.z();
    modelMatrix(3,3) = 1;

    return modelMatrix;

}





QVector3D Transform::applyToPoint(QVector3D p)
{
    return ( rotate.rotatedVector(p) * scale) + position   ;
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
    t = (rotate.rotatedVector(t) + position )* scale;
            //???scale * ( e * p) + translate
    return QVector4D(t.x(), t.y(), t.z(), p.w());
}

Transform Transform::combine_with(Transform &t)
{


    Transform res = Transform( rotate * t.rotate,  position + t.position,  scale * t.scale);
    return (res);
}


QMatrix4x4 Transform::inverseWorld(){
    return matrix.inverted();

}

QVector3D Transform::getWorldTranslate(){
    return QVector3D(this->matrix(0,3), this->matrix(1,3), this->matrix(2,3));


}


