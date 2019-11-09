#pragma once

#include <qgl.h>
#include <pcl/apps/point_cloud_editor/toolInterface.h>
#include <pcl/apps/point_cloud_editor/localTypes.h>
#include <QLabel>
class DisplayDepthValue
{
public:
    DisplayDepthValue(CloudPtr cloud_ptr_);
    ~DisplayDepthValue();
    //判断点是否在鼠标位置上
    bool isRightPoint(const Point3D& pt,const GLfloat* project,const GLint *viewport) const;
    //得到深度值
    void getDepthValue(int x, int y,const QPointF pos);
    QLabel *label;
private:
    CloudPtr cloud_ptr_;
    //将空间坐标点转换成屏幕坐标点
    //鼠标的坐标位置 xy
    float screen_pos_x;
    float screen_pos_y;
    QPointF screen_pos;
    float mistake_dis=0.001;
    float depth_value;
    QPainter *painter;

};
