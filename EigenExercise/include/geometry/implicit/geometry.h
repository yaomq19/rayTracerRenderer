#ifndef IMPLICIT_GEOMETRY_H
#define IMPLICIT_GEOMETRY_H
#include <vector>
#include <Eigen/Dense>
#include "sphere.h"
using Eigen::Vector3f;
using Eigen::Matrix3f;
class Material
{
    public:
    Matrix3f kd,ks,ka;
    float pp;
    Material& operator=(Material b);
};
class Surface
{
    public:
    uint32_t id;
    std::vector<Vector3f> vertexs; 
    Material material;
};
class Vertex
{
    public:
    Vector3f position;
    //other properties
    //...
    float x(){return position[0];}
    float y(){return position[1];}
    float z(){return position[2];}
};
class Triangle
{
    public:
    Vertex vertex[3];
};
class IndexedMesh
{
    public:
    uint32_t nv,nt;
    int** tInd;
    Vector3f* vertices;
    IndexedMesh(){}
    IndexedMesh(uint32_t nnvv,uint32_t nntt );
    ~IndexedMesh();
};
class Polygon 
{
    public:
    std::vector<Vertex> vertex;

};
class Sphere
{
    public:
    float x0,y0,z0,R;
};
#endif