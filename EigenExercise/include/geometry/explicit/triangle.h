#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "vertex.h"
#include "face.h"
#include <vector>
#define CYCLIC 1
//Triangle为三角形单面，类内包含顶点实体
class Triangle
{
    public:
    Vertex vertices[3];
    TriFace face;
    public:
    Triangle()
    {
        face.index[0]=0;
        face.index[1]=1;
        face.index[2]=2;
    }
    ~Triangle()
    {
    }
};
class TriangleFan
{
    public:
    std::vector<Vertex> vertices;
    std::vector<TriFace> faces;
    public:
    TriangleFan(){}
    ~TriangleFan(){}
};
class TriangleStrips
{
    public:
    std::vector<Vertex> vertices;
    std::vector<TriFace> faces;
    public:
    TriangleStrips(){}
    ~TriangleStrips(){}
};
#endif