#ifndef AABB_H
#define AABB_H

#include <QVector3D>
#include "intersectdata.h"
#include "algorithm"
#include "transform.h"


class AABB
{
public:
    AABB(const QVector3D& mincorner, const QVector3D& maxcorner) :
     m_minCorner(mincorner),
     m_maxCorner(maxcorner)
    {};

    IntersectData IntersectAABB(const AABB& other);

    inline const QVector3D getMinCorner() const {return m_minCorner;}
    inline const QVector3D getMaxCorner() const {return m_maxCorner;}

private:
    const QVector3D m_minCorner;
    const QVector3D m_maxCorner;
};

#endif // AABB_H
