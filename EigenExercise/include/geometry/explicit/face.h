#ifndef SURFACE_H
#define SURFACE_H
#include "vertex.h"
#include <vector>
#include "../../ray.h"

//Face为多边形小面，类本身中并不存储顶点实体，可以被包含在有顶点（如网格）的复杂类中使用
class Face
{
    public:
    int number;       //面的顶点数目
    int *index;         //面的顶点索引号
    public:
    Face(){}
    virtual ~Face(){}
    bool virtual operator==(Face b)
    {
        if(this->number!=b.number)return false;
        else
        {
            for(int i=0;i<this->number;i++)
            {
                if(this->index[i]!=b.index[i])
                {
                    return false;
                }
            }
        }
        return true;
    }
    bool virtual operator!=(Face b)
    {
        return !(*this==b);
    }
};
class TriFace:public Face
{
    public:
    TriFace()
    {
        this->number=3;
        this->index=new int[3];
    }
    TriFace(int a,int b,int c)
    {
        this->number=3;
        this->index=new int[3];
        index[0]=a;
        index[1]=b;
        index[2]=c;
    }
    void set(int a,int b,int c)
    {
        index[0]=a;
        index[1]=b;
        index[2]=c;
    }
    ~TriFace()
    {
    }
    bool operator==(TriFace b)
    {
        for(int i=0;i<3;i++)
        {
            if(this->index[i]!=b.index[i])
            {
                return false;
            }
        }
        return true;
    }
};

#endif