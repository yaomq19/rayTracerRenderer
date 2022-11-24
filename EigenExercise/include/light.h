#ifndef LIGHT_H
#define LIGHT_H
#include <Eigen/Dense>
#include "color.h"
using Eigen::Matrix3f;
class Light
{
    public:
};
class PointLight:public Light
{
    public:
    //点光源的颜色
    Color I;
    //点光源的位置
    Vector3f p;
    PointLight(){}
    PointLight(Color color,Vector3f vec3f);
};
class AmbientLight:public Light
{
    public:
    Color Ia;
    AmbientLight(){}
    AmbientLight(Color I);
};
#endif