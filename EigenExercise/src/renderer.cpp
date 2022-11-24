#include "../include/renderer.h"
#define RENDER_MSAA 1
float maxx(float a,float b)
{
    return (a>b) ? a : b;
}
Renderer::Renderer(int width,int height)
{
    u=Vector3f(1,0,0);
    v=Vector3f(0,1,0);
    w=Vector3f(0,0,1);
    eye=Vector3f(0,0,0);

    right=1;
    left=-1*right;
    top=height*1.f/width;
    bottom=-1*top;

    nx=width;
    ny=height;
    m_width=width;
    m_height=height;
    distance=1;

    modelMatrix=Matrix4f::Identity();
    frame_buf.clear();
    vertex_list.clear();
    face_list.clear();
    pl_list.clear();
    al_list.clear();
}
void Renderer::set_distance(double input)
{
    this->distance=input;
}
void Renderer::load_model(const SphereMeshTri& s)
{
    //记录当前vertex_list长度
    int pre_length=vertex_list.size();
    vertex_list.insert(vertex_list.end(),s.vertices.begin(),s.vertices.end());
    std::vector<TriFace> medium=s.faces;
    for(auto it=medium.begin();it!=medium.end();it++)
    {
        it->index[0]+=pre_length;
        it->index[1]+=pre_length;
        it->index[2]+=pre_length;
    }
    face_list.insert(face_list.end(),medium.begin(),medium.end());
}
void Renderer::load_model(const Triangle& tri)
{
}
void Renderer::load_lights(const std::vector<PointLight>& p,const std::vector<AmbientLight>& a)
{
    pl_list=p;
    al_list=a;
}
Ray Renderer::ray_generation(int i,int j,float t1,float t2)
{
    float x=left+(right-left)*(j+0.5f)/nx;
    float y=top+(bottom-top)*(i+0.5f)/ny;
    Ray res;
    res.o=eye;
    res.d=-1*distance*w+x*u+y*v;
    res.t1=t1;
    res.t2=t2;
    return res;
}
HitRecord Renderer::ray_intersection(const Ray& ray,const TriFace& face)
{
    float t;
    Vector3f n;
    int id0=face.index[0];
    int id1=face.index[0];
    int id2=face.index[0];
    Vector3f p0=vertex_list[id0].position;
    Vector3f p1=vertex_list[id1].position;
    Vector3f p2=vertex_list[id2].position;
    if(face.number==3)
    {
        Vector3f e1=p1-p0;
        Vector3f e2=p2-p0;
        Vector3f o=ray.o;
        Vector3f d=ray.d;
        n=e1.cross(e2);
        Vector3f s=o-p0;
        Vector3f s1=d.cross(e2);
        Vector3f s2=s.cross(e1);
        float b1=s1.dot(s)/s1.dot(e1);
        float b2=s2.dot(d)/s1.dot(e1);
        if(b1>0&&b1<1&&b2>0&&b2<1&&(1-b1-b2)>0&&(1-b1-b2)<1)
        {
            t=s2.dot(e2)/s1.dot(e1);
            if(t<ray.t1||t>ray.t2)
            {
                t=INFINITY;
            }
        }
        else t=INFINITY;
    }
    HitRecord res(face,ray,t,n);
    return res;
}
Vector3f Renderer::fill_color(int i,int j)
{
    //每个像素的默认颜色为黑色
    Vector3f res_color(0,0,0);
    //生成和i，j像素对应的光线
    Ray ray_origin=ray_generation(i,j,1,100000);
    TriFace facetool;Ray raytool;
    HitRecord hit(facetool,raytool,INFINITY,Vector3f(0,0,0));
    for(auto it=face_list.begin();it!=face_list.end();it++)
    {
        //对每个表面求交
        TriFace face_para=*it;
        HitRecord hit_temp=ray_intersection(ray_origin,face_para);
        if(hit_temp.t<hit.t)
        {
            hit=hit_temp;
        }
    }
    //如果光线有命中表面
    if(hit.t!=INFINITY)
    {
        //对于每个点光源进行可见性测试
        for(auto it2=pl_list.begin();it2!=pl_list.end();it2++)
        {
            if(isVisibleForPLight(hit,*it2))
            {
                Color sub_contribution=illuminate(ray_origin,hit,*it2);
                res_color=res_color+sub_contribution;
            }
        }
        for(auto it3=al_list.begin();it3!=al_list.end();it3++)
        {
            Color sub_contribution=illuminate(ray_origin,hit,*it3);
            res_color=res_color+sub_contribution;
        }
    }
    return res_color;
}
Vector3f Renderer::fill_color_MSAA(int i,int j)
{
    //每个像素的默认颜色为黑色
    Vector3f res_color_sub[4];
    for(int ii=0;ii<4;ii++)
    {
        res_color_sub[ii]=Vector3f(0.f,0.f,0.f);
    }
    //生成和i，j像素对应的光线
    Ray ray_origin=ray_generation(i,j,1,100000);
    Ray ray[4];
    float delta[4][2]={
        -1.f/(nx*4),1.f/(ny*4),
        1.f/(nx*4),1.f/(ny*4),
        -1.f/(nx*4),-1.f/(ny*4),
        1.f/(nx*4),-1.f/(ny*4)
    };
    for(int ii=0;ii<4;ii++)
    {
        ray[ii]=ray_origin;
        ray[ii].d[0]+=delta[ii][0];
        ray[ii].d[1]+=delta[ii][1];
    }
    TriFace facetool;Ray raytool;
    HitRecord hit(facetool,raytool,INFINITY,Vector3f(0,0,0));
    for(int ii=0;ii<4;ii++)
    {
        for(auto it=face_list.begin();it!=face_list.end();it++)
        {
            //对每个表面求交
            TriFace face_para=*it;
            HitRecord hit_temp=ray_intersection(ray[ii],face_para);
            if(hit_temp.t<hit.t)
            {
                hit=hit_temp;
            }
        }
        //如果光线有命中表面
        if(hit.t!=INFINITY)
        {
            //对于每个点光源进行可见性测试
            for(auto it2=pl_list.begin();it2!=pl_list.end();it2++)
            {
                if(isVisibleForPLight(hit,*it2))
                {
                    Color sub_contribution=illuminate(ray[ii],hit,*it2);
                    res_color_sub[ii]=res_color_sub[ii]+sub_contribution;
                }
            }
            for(auto it3=al_list.begin();it3!=al_list.end();it3++)
            {
                Color sub_contribution=illuminate(ray[ii],hit,*it3);
                res_color_sub[ii]=res_color_sub[ii]+sub_contribution;
            }
        }
    }
    Color res_color(0.f,0.f,0.f);
    for(int ii=0;ii<4;ii++)
    {
        res_color+=res_color_sub[ii];
    }
    res_color/=4;
    return res_color;
}
bool Renderer::isVisibleForPLight(const HitRecord& hit, const PointLight& pl)
{
    bool res = true;
    //从测试点发向光源的射线ray_temp
    Ray ray_temp;
    ray_temp.o=hit.ray.evaluate(hit.t);
    ray_temp.d=pl.p-ray_temp.o;
    ray_temp.t1=0;
    ray_temp.t2=100000;
    for(auto it=face_list.begin();it!=face_list.end();it++)
    {
        //对每个surface测试
        HitRecord hit_temp = ray_intersection(ray_temp,*it);
        //一旦有遮挡
        if(hit_temp.t!=INFINITY)
        {
            //只有被其他表面遮挡才算，置为false不可见
            if(hit_temp.face != *it)
            {
                res=false;
            }
        }
    }
    return res;
}
Color Renderer::illuminate(Ray ray,HitRecord hrec,PointLight light)
{
    Color res_color(0,0,0);
    //计算着色点位置x
    Vector3f x=ray.evaluate(hrec.t);
    //未归一化的l向量
    Vector3f l=light.p-x;
    //x和p之间的距离记为r
    float r=l.norm();
    //对l归一化
    l.normalize();

    Vector3f v=-1*ray.d;
    v.normalize();

    Vector3f n=hrec.n;
    n.normalize();
    //半程向量
    Vector3f h=(v+l).normalized();
    
    int index=hrec.face.index[0];

    Matrix3f kd=vertex_list[index].kd;
    Matrix3f ks=vertex_list[index].ks;
    
    float pp=vertex_list[index].pp;
    Color Ld=kd*(light.I/(r*r))*maxx(0,n.dot(l));
    Color Ls=ks*(light.I/(r*r))*pow(maxx(0,n.dot(h)),pp);
    
    res_color=res_color+Ld+Ls;
    return res_color;
}
Color Renderer::illuminate(Ray ray,HitRecord hrec,AmbientLight light)
{
    Color res_color(0,0,0);
    int index=hrec.face.index[0];
    Matrix3f ka=vertex_list[index].ka;

    Color La=ka*light.Ia;
    res_color=res_color+La;
    return res_color;
}
void Renderer::rotate(Vector3f eye_pos)
{
    //根据eye_pos旋转修改surface_list里面的内容
}
Mat Renderer::render(Vector3f eye_pos,int grade,int mode)
{
    frame_buf.clear();
    this->eye=eye_pos;
    rotate(eye);
    for(int i=0;i<ny;i++)
    {
        for(int j=0;j<nx;j++)
        {
            if(mode==0)
            {
                fill_color(i,j);
            }
            else if(mode==RENDER_MSAA)
            {
                frame_buf.push_back(fill_color_MSAA(i,j));
            }
            if(j==699)
            {
                std::cout<<"have finished for:    "<<i<<"/700"<<std::endl;
            }
        }
    }
    if(grade>0)
    {
        for(int i=0;i<ny;i++)
        {
            for(int j=0;j<nx;j++)
            {
                Vector3f pixel_sum(0.f,0.f,0.f);
                if(i>=grade&&i<=ny-1-grade&&j>=grade&&j<=nx-1-grade)
                {
                    for(int p=i-grade;p<=i+grade;p++)
                    {
                        for(int q=j-grade;q<=j+grade;q++)
                        {
                            pixel_sum+=frame_buf[p*nx+q];
                        }
                    }
                }
                int div=(grade*2+1)*(grade*2+1);
                frame_buf[i*nx+j]=pixel_sum/div;
            }
        }
    }
    Mat image(m_height, m_width, CV_32FC3, frame_buf.data());
    image.convertTo(image, CV_8UC3, 1.0f);
    cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
    return image;
}
