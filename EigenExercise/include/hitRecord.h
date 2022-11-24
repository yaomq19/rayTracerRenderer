#ifndef HITRECORD_H
#define HITRECORD_H
#include <Eigen/Dense>
#include "ray.h"
#include "geometry/explicit/geometry.h"
using Eigen::Vector3f;
class HitRecord
{
    public:
    TriFace face;
    Ray ray;
    float t;
    Vector3f n;
    HitRecord(){}
    HitRecord(TriFace tri,Ray r,float tt,Vector3f nn)
    {
        face=tri;
        ray=r;
        t=tt;
        n=nn;
    }
};
#endif