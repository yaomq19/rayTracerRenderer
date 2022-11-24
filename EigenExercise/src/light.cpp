#include "../include/light.h"
PointLight::PointLight(Color color,Vector3f vec3f)
{
    I=color;
    p=vec3f;
}
AmbientLight::AmbientLight(Color I)
{
    Ia=I;
}