#ifndef VERTEX_H
#define VERTEX_H
#include <vector>
#include <Eigen/Dense>
using Eigen::Vector3f;
using Eigen::Matrix3f;
class Material
{
    public:
    Matrix3f kd,ks,ka;
    float pp;
    Material& operator=(Material b);
};

class Vertex
{
    public:
    Vector3f position;
    //other properties
    Matrix3f kd,ks,ka;                    //漫反射系数、高光系数、环境光系数
    float pp;                                   //高光指数
    //...
    float& x(){return position[0];}
    float& y(){return position[1];}
    float& z(){return position[2];}
    Vertex(){}
    Vertex(Vector3f pos,Vector3f kkdd,Vector3f kkss,Vector3f kkaa,float ppp)
    {
        position=pos;
        kd.Identity();
        ks.Identity();
        ka.Identity();
        kd(0,0)=kkdd[0]/255.f;
        kd(1,1)=kkdd[1]/255.f;
        kd(2,2)=kkdd[2]/255.f;

        ks(0,0)=kkss[0]/255.f;
        ks(1,1)=kkss[1]/255.f;
        ks(2,2)=kkss[2]/255.f;

        ka(0,0)=kkaa[0]/255.f;
        ka(1,1)=kkaa[1]/255.f;
        ka(2,2)=kkaa[2]/255.f;
        pp=ppp;
    }
    void set(Vector3f pos,Vector3f kkdd,Vector3f kkss,Vector3f kkaa,float ppp)
    {
        position=pos;
        kd.Identity();
        ks.Identity();
        ka.Identity();
        kd(0,0)=kkdd[0]/255.f;
        kd(1,1)=kkdd[1]/255.f;
        kd(2,2)=kkdd[2]/255.f;

        ks(0,0)=kkss[0]/255.f;
        ks(1,1)=kkss[1]/255.f;
        ks(2,2)=kkss[2]/255.f;

        ka(0,0)=kkaa[0]/255.f;
        ka(1,1)=kkaa[1]/255.f;
        ka(2,2)=kkaa[2]/255.f;
        pp=ppp;
    }
};



#endif