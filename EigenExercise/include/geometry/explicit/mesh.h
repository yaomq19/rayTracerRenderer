#ifndef MESH_H
#define MESH_H
#include <vector>
#include <string>
#include "vertex.h"
#include "triangle.h"
#include "../../ray.h"
class SphereMeshTri
{
    public:
    int N1,N2;
    Vector3f O;
    float r;
    std::vector<Vertex> vertices;
    std::vector<TriFace> faces;
    public:
    SphereMeshTri(){}
    ~SphereMeshTri(){}
    void read(std::string filename);
};
#endif