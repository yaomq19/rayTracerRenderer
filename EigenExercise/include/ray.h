#ifndef RAY_H
#define RAY_H
#include <Eigen/Dense>
using Eigen::Vector3f;
class Ray
{
    public:
    Vector3f o;
    Vector3f d;
    float t1, t2;
    Ray();
    Ray(Vector3f origin,Vector3f direction,float time1,float time2);
    Vector3f evaluate(float t);
    Vector3f evaluate(float t)const;
};
#endif