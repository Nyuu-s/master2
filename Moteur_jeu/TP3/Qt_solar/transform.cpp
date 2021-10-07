#include "transform.h"

Transform::Transform()
{

}

Transform::Transform(QMatrix4x4 m, QQuaternion r, QVector3D trans): matrix(m), rotate(r), translate(trans){
    matrix = m;
    rotate = r;
    translate = trans;
}
