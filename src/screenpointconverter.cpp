#include <pcl/apps/point_cloud_editor/screenpointconverter.h>
#include <pcl/apps/point_cloud_editor/cloud.h>
#include <QApplication>
#include <QToolTip>
Converter::Converter(CloudPtr CloudPtr)
{
    cloud_ptr_=CloudPtr;
}

bool
Converter::isRightPoint(const Point3D& pt,
                             const GLfloat* project,
                                 const GLint *viewport) const
{//将三维坐标点转换成平面坐标点
  float w = pt.z * project[11];
  float x = (pt.x * project[0] + pt.z * project[8]) / w;
  float y = (pt.y * project[5] + pt.z * project[9]) / w;
//将屏幕坐标点转换成以屏幕中心为原点的坐标系上的点
  float screen_x = screen_pos_x/(viewport[2]*0.5) - 1.0;
  float screen_y = screen_pos_y/(viewport[3]*0.5) - 1.0;
  // Ignore the points behind the camera
  //计算点之间的距离
  float displace_x=std::abs(screen_x-x);
  float displace_y=std::abs(screen_y-y);
  //当距离小于误差值的时候,认为到达该点
  if(displace_x<=mistake_dis&&displace_y<=mistake_dis)
      return true;
  else
      return false;
}

Converter::~Converter()
{}


//首先应该判断鼠标事件是不是停止
bool
Converter::getDepthValue(int x, int y,Point3D& point)
{
  if (!cloud_ptr_)
    return false;
  screen_pos_x= x;
  screen_pos_y = y;
  GLint viewport[4];
  glGetIntegerv(GL_VIEWPORT,viewport);
  GLfloat project[16];
  glGetFloatv(GL_PROJECTION_MATRIX, project);
  Point3DVector ptsvec;
  cloud_ptr_->getDisplaySpacePoints(ptsvec);
  for(std::size_t i = 0; i < ptsvec.size(); ++i)
  {
    Point3D pt = ptsvec[i];
    if (isRightPoint(pt, project, viewport))
    {
        point=cloud_ptr_->getObjectSpacePoint(i);
        return true;
    }
  }
  return false;
}
