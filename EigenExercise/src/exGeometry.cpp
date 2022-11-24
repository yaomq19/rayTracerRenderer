#include "../include/geometry/explicit/geometry.h"
#include <fstream>
#include <iostream>
#include <math.h>
#define PI 3.1415926
Material& Material::operator=(Material b)
{
    this->kd=b.kd;
    this->ks=b.ks;
    this->ka=b.ka;
    this->pp=b.pp;
    return *this;
}
void SphereMeshTri::read(std::string filename)
{
    std::ifstream ifs;
    ifs.open(filename);
    if(!ifs.is_open())std::cout<<"open file error!"<<std::endl;
    std::string str;
    int alpha,beta,pp;
    Vector3f kd,ks,ka;
    int tool;
    while(!ifs.eof())
    {
        ifs>>str;
        if(str=="o")
        {
            ifs>>O[0]>>O[1]>>O[2];
        }
        else if(str=="r")
        {
            ifs>>r;
        }
        else if(str=="alpha")
        {
            ifs>>alpha;
        }
        else if(str=="beta")
        {
            ifs>>beta;
        }
        else if(str=="kd")
        {
            ifs>>kd[0]>>kd[1]>>kd[2];
        }
        else if(str=="ks")
        {
            ifs>>ks[0]>>ks[1]>>ks[2];
        }
        else if(str=="ka")
        {
            ifs>>ka[0]>>ka[1]>>ka[2];
        }
        else if(str=="pp")
        {
            ifs>>pp;
        }
        else{
            ifs>>tool;
        }
    }
    N1=180/alpha;
    N2=360/beta;
    double alpha1,beta1;
    Vertex v(Vector3f(O[0],O[1]+r,O[2]),kd,ks,ka,pp);
    vertices.push_back(v);
    for(int i=0;i<N1-1;i++)
    {
        alpha1=(i+1)*alpha*PI/180;
        for(int j=0;j<N2;j++)
        {
            beta1=j*beta*PI/180;
            float x,y,z;
            x=sin(alpha1)*sin(beta1);
            y=cos(alpha1);
            z=sin(alpha1)*cos(beta1);
            v.set(Vector3f(x,y,z),kd,ks,ka,pp);
            vertices.push_back(v);
        }
    }
    v.set(Vector3f(O[0],O[1]-r,O[2]),kd,ks,ka,pp);
    vertices.push_back(v);

    //设置面，关键步骤
    for(int j=0;j<N2;j++)
    {
        int tempj=j+1;
        if(N2==tempj)tempj=0;
        TriFace f(0,j+1,tempj+1);
        faces.push_back(f);
    }
    for(int i=1;i<N1-1;i++)
    {
        for(int j=0;j<N2;j++)
        {
            int tempi=i+1;
            int tempj=j+1;
            if(N2==tempj)tempj=0;
            int BodyIndex[3];
            BodyIndex[0]=(i-1)*N2+j+1;
            BodyIndex[1]=(tempi-1)*N2+j+1;
            BodyIndex[2]=(tempi-1)*N2+tempj+1;
            TriFace f(BodyIndex[0],BodyIndex[1],BodyIndex[2]);
            faces.push_back(f);
            BodyIndex[0]=(i-1)*N2+j+1;
            BodyIndex[1]=(tempi-1)*N2+tempj+1;
            BodyIndex[2]=(i-1)*N2+tempj+1;
            f.set(BodyIndex[0],BodyIndex[1],BodyIndex[2]);
            faces.push_back(f);
        }
    }
    for(int j=0;j<N2;j++)
    {
        int tempj=j+1;
        if(N2==tempj)tempj=0;
        int SouthIndex[3];
        SouthIndex[0]=(N1-2)*N2+j+1;
        SouthIndex[1]=(N1-1)*N2+1;
        SouthIndex[2]=(N1-2)*N2+tempj+1;
        TriFace f(SouthIndex[0],SouthIndex[1],SouthIndex[2]);
        faces.push_back(f);
    }
}