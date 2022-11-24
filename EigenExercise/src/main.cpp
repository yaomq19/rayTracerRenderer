#include <iostream>
#include "../include/model.h"
#include "../include/renderer.h"
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
#include <vector>
#include <fstream>
using Eigen::Matrix3f;
using namespace std;
using namespace cv;
void test01()
{
  SphereMeshTri sm;
  //吧数据读到sm中
  sm.read("data_spMesh.txt");
  std::vector<PointLight> pl_list;
  std::vector<AmbientLight> al_list;
  PointLight pl(Color(4000000,4000000,4000000),Vector3f(2,2,2));
  AmbientLight al(Color(0,0,0));
  pl_list.push_back(pl);
  al_list.push_back(al);

  PointLight pl2(Color(4000000,4000000,4000000),Vector3f(0,110,-200));
  pl_list.push_back(pl2);

  Renderer r(700,700);
  r.set_distance(1);

  r.load_lights(pl_list,al_list);
  r.load_model(sm);
  
  Mat image0=r.render(Vector3f(0,0,0),0);
  imwrite("../image/output0.png",image0);
  // Mat image1=r.render(Vector3f(0,0,0),1);
  // imwrite("output1.png",image1);
  //Mat image2=r.render(Vector3f(0,0,0),2);
  //imwrite("output2.png",image2);
  waitKey(0);
}
int main()
{
  test01();
  return 0;
}