#ifndef TRANSFORM_H
#define TRANSFORM_H


#include <QVector2D>
#include <QVector3D>
#include<QMatrix4x4>


class Transform
{

public:
    Transform();
    Transform(QQuaternion rotate, QVector3D trans, float s);

    //fields
    QMatrix4x4  matrix; // world transform

    //local transform
    float       scale;  //uniform scale
    QQuaternion rotate;
    QVector3D   position;

    //methods
    QMatrix4x4 getModelMatrix();
    QMatrix4x4 getLocalModelMatrix();



    void computeModelMatrix();
    void computeModelMatrix(const QMatrix4x4 &parentMatrix);





    QVector4D apply(QVector4D p);
    QVector3D applyToPoint(QVector3D  p);
    QVector3D applyToVector(QVector3D v);
    QVector3D applyToVersor(QVector3D v);
    Transform combine_with(Transform &t);
    Transform inverse();

    Transform interpolate(Transform &t, float k){
        Transform result;
        result.scale = this->scale * k +t.scale *(1-k);                 // scale interpolation
        rotate.slerp(this->rotate, t.rotate, k);                        // spherical linear interpolation for quaternions
       // result.rotate = this->rotate.mix_with(b.rotate, k);
        result.position = this->position * k+t.position * (1-k);     // translation interpolation
        return result;
    }


    Transform operator*(Transform& local)
    {
        Transform res_test1 = Transform(this->rotate * local.rotate, this->position + local.position, this->scale * local.scale);
        Transform res_test2 = Transform( local.rotate * this->rotate,  local.position + this->position, local.scale * this->scale);

        return res_test1;
        //return this->combine_with(local);
    }

};



#endif // TRANSFORM_H
