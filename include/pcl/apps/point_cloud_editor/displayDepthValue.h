#pragma once

#include <qgl.h>
#include <pcl/apps/point_cloud_editor/toolInterface.h>
#include <pcl/apps/point_cloud_editor/localTypes.h>

class DisplayDepthValue
{
public:
    DisplayDepthValue(CloudPtr cloud_ptr_);
    ~DisplayDepthValue();
    float getDepthValue(const Point3D& pt, const GLfloat* project);
private:
    CloudPtr cloud_ptr_;
    //将空间坐标点转换成屏幕坐标点
    void convertValue(Point3D* pt,Point3D& pt);

}
