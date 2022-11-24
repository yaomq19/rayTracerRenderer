#ifndef RENDERER_H
#define RENDERER_H
#include <iostream>
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
#include <vector>

#include "model.h"
#include "ray.h"
#include "color.h"
#include "hitRecord.h"
#include "light.h"

using Eigen::Vector3f;
using Eigen::Matrix4f;
using namespace cv;
class Renderer
{
    public:
    //坐标系
    Vector3f u,v,w;
    //视点
    Vector3f eye;
    //视平面边框
    float left,right,top,bottom;
    //和视平面的距离
    float distance;
    //水平方向和竖直方向像素个数
    int nx,ny;
    //宽和高，（即ny和nx的换一种说法）
    int m_width,m_height;
    //图像缓冲区
    std::vector<Color> frame_buf;
    //点集
    std::vector<Vertex> vertex_list;
    //表面集
    std::vector<TriFace> face_list;
    //光源集合
    std::vector<PointLight> pl_list;
    std::vector<AmbientLight> al_list;
    //Model矩阵
    Matrix4f modelMatrix;

    Renderer(int width=0,int height=0);
    void set_distance(double input);
    //加载模型
    void load_model(const SphereMeshTri& s);
    void load_model(const Triangle& tri);
    //加载光源信息
    void load_lights(const std::vector<PointLight>& p,const std::vector<AmbientLight>& a);
    //射线生成
    Ray ray_generation(int i,int j,float t1,float t2);
    HitRecord ray_intersection(const Ray& ray,const TriFace& face);
    //判断可见性
    bool isVisibleForPLight(const HitRecord& hit, const PointLight& pl);
    //对第i，j个像素着色
    Vector3f fill_color(int i,int j);
    Vector3f fill_color_MSAA(int i,int j);
    //进行照射，返回Color
    Color illuminate(Ray ray,HitRecord hrec,PointLight light);
    Color illuminate(Ray ray,HitRecord hrec,AmbientLight light);
    void rotate(Vector3f eye_pos);
    Mat render(Vector3f eye_pos,int grade,int mode=0);
};


#endif