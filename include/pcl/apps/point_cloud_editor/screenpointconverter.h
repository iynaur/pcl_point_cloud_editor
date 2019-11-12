#pragma once

#include <qgl.h>
#include <pcl/apps/point_cloud_editor/toolInterface.h>
#include <pcl/apps/point_cloud_editor/localTypes.h>
class Converter{
public:
    Converter(CloudPtr cloud_ptr_);
    ~Converter();
    //判断点是否在鼠标位置上
    bool isRightPoint(const Point3D& pt,const GLfloat* project,const GLint *viewport) const;
    //得到深度值
    bool getDepthValue(int x, int y,Point3D& point);
private:
    CloudPtr cloud_ptr_;
    //将空间坐标点转换成屏幕坐标点
    //鼠标的坐标位置 xy
    float screen_pos_x;
    float screen_pos_y;
    float mistake_dis=0.01;
    float depth_value;
};
