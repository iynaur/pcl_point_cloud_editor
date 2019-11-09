#include <pcl/apps/point_cloud_editor/displayDepthValue.h>
#include <pcl/apps/point_cloud_editor/cloud.h>

DisplayDepthValue::DisplayDepthValue(CloudPtr CloudPtr)
{
    cloud_ptr_=CloudPtr;
}

bool
DisplayDepthValue::getDepthValue(const Point3D& pt,
                             const GLfloat* project) const
{//将三维坐标点转换成平面坐标点
  float w = pt.z * project[11];
  float x = (pt.x * project[0] + pt.z * project[8]) / w;
  float y = (pt.y * project[5] + pt.z * project[9]) / w;

  float min_x = std::min(origin_x_, final_x_)/(viewport[2]*0.5) - 1.0;
  float max_x = std::max(final_x_, origin_x_)/(viewport[2]*0.5) - 1.0;
  float max_y = (viewport[3] - std::min(origin_y_, final_y_))/(viewport[3]*0.5) - 1.0;
  float min_y = (viewport[3] - std::max(origin_y_, final_y_))/(viewport[3]*0.5) - 1.0;
  printf("min_x=%f max_x=%f min_y=%f max_y=%f",min_x,max_x,min_y,max_y);
  printf(("x=%f y=%f w=%f"));
  // Ignore the points behind the camera
  if (w < 0)
    return (false);
  // Check the left and right sides
  if ((x < min_x) || (x > max_x))
    return (false);
  // Check the bottom and top
  if ((y < min_y) || (y > max_y))
    return (false);
  return (true);
}
