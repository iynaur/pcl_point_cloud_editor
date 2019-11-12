#include <pcl/apps/point_cloud_editor/ranging.h>
#include <algorithm>
#include <math.h>
#include <QToolTip>
#include <QWidget>


Ranging::Ranging(boost::shared_ptr<RangingDialog> m_dialog)
{
    dialog=m_dialog;
}

Ranging::~Ranging()
{

}
void
Ranging::getPoint3D(int x, int y,const QPointF screen_pos,boost::shared_ptr<Converter> converter)
{
    Point3D point;
    QString str1,str2;
    if(converter->getDepthValue(x,y,point))
    {
        str2.append(QString::number(point.x));
        str2.append(",");
        str2.append(QString::number(point.y));
        str2.append(",");
        str2.append(QString::number(point.z));
        str2.append(")");
        if(times==0){
            point1=point;
            str1=QString("第一个点(");
            point1str.append(str1);
            point1str.append(str2);
        }
        else
        {
            point2=point;
            str1=QString("第二个点(");
            point2str.append(str1);
            point2str.append(str2);

        }

        QToolTip::showText(screen_pos.toPoint(),str1.append(str2));
        times++;
        qDebug("转换成了点 %d",times);
    }
    else
    {
         str1.append("没有选中任何点");
         QToolTip::showText(screen_pos.toPoint(),str1);
    }
}

void
Ranging::reset()
{
    times=0;
    point1str.clear();
    point2str.clear();
    resultstr.clear();
}

float
Ranging::getDistanceOfPoints()
{
float disx=std::abs(point1.x-point2.x);
float disy=std::abs(point1.y-point2.y);
float disz=std::abs(point1.z-point2.z);
qDebug("%f %f %f %f %f %f",point1.x,point1.y,point1.z,point2.x,point2.y,point2.z);

 distance=sqrt(disx*disx+disy*disy+disz*disz);
qDebug("distance : %f",distance);
return sqrt(disx*disx+disy*disy+disz*disz);

}

void
Ranging::onMouseReleased(int x,int y,const QPointF screen_pos,boost::shared_ptr<Converter> converter)
{
    qDebug("times %d",times);
    //如果没有移动位置
    if(final_x==x&&final_y==y)
    {
        getPoint3D(x,y,screen_pos,converter);
    }
    if(times==2)
    {
        //TODO 显示距离
        qDebug("两点之间的距离为:%f",getDistanceOfPoints());
        resultstr.append(QString("距离为:")).append(QString::number(distance));
        dialog->ShowDialog(point1str,point2str,resultstr);
        reset();
    }
}

void Ranging::onMousePressed(int x,int y)
{
    final_x=x;
    final_y=y;
}



