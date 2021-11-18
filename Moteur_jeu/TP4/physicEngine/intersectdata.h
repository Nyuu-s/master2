#ifndef INTERSECTDATA_H
#define INTERSECTDATA_H


class IntersectData
{
public:
    IntersectData(const bool doesIntersect, const float distance) :
        m_isIntersect(doesIntersect),
        m_distance(distance)
    {};

    inline bool IsIntersect() const {return m_isIntersect;}
    inline bool getDistance() const {return m_distance;}


private:
    const bool m_isIntersect;
    const float m_distance;
};

#endif // INTERSECTDATA_H
