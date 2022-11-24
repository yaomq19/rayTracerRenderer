#include "../include/ray.h"
Ray::Ray()
{
    this->o=Vector3f(0,0,0);
    this->d=Vector3f(1,1,1);
    t1=0;
    t2=100000;
}
Ray::Ray(Vector3f origin,Vector3f direction,float time1,float time2)
{
    this->o=origin;
    this->d=direction;
    t1=time1;
    t2=time2;
}
Vector3f Ray::evaluate(float t)
{
    return o+t*d;
}
Vector3f Ray::evaluate (float t)const
{
    return o+t*d;
}