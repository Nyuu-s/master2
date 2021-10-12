#ifndef TRANSFORM_H
#define TRANSFORM_H


#include <QVector2D>
#include <QVector3D>
#include<QMatrix4x4>


class Transform
{

public:
    Transform();
    Transform(QMatrix4x4 matrix, QQuaternion rotate, QVector3D trans, float s);

    //fields
    QMatrix4x4 matrix;
    float scale; //uniform scale
    QQuaternion rotate;
    QVector3D translate;

    //methods
    QVector4D apply(QVector4D p);
    QVector3D applyToPoint(QVector3D  p);
    QVector3D applyToVector(QVector3D v);
    QVector3D applyToVersor(QVector3D v);
    Transform combine_with(Transform &t);
    Transform inverse();
    Transform interpolate(Transform &t, float k);

    Transform mix_with(Transform b, float k){
        Transform result;
        result.scale = this->scale * k +b.scale *(1-k);
       // result.rotate = this->rotate.mix_with(b.rotate, k);
        result.translate = this->translate * k+b.translate * (1-k);
        return result;
    }




};



#endif // TRANSFORM_H
