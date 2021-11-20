#ifndef INTERSECTDATA_H
#define INTERSECTDATA_H

#include <QVector3D>

class IntersectData
{
public:
    IntersectData(const bool doesIntersect, const QVector3D direction) :
        m_isIntersect(doesIntersect),
        m_direction(direction)
    {};

    inline bool IsIntersect() const {return m_isIntersect;}
    inline float getDistance() const {return m_direction.length();}
    inline QVector3D getDirection() const {return m_direction;}


private:
    const bool m_isIntersect;
    const QVector3D m_direction;
};

#endif // INTERSECTDATA_H
