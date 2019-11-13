#include <pcl/apps/point_cloud_editor/ranging.h>
#include <algorithm>
#include <math.h>
#include <QToolTip>
#include <QWidget>


Ranging::Ranging()
{
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
           // setHighlightColor(point1);
        }
        else
        {
            point2=point;
            str1=QString("第二个点(");
            point2str.append(str1);
            point2str.append(str2);
            //setHighlightColor(point2);

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
        QToolTip::showText(screen_pos.toPoint(),resultstr);
        reset();
    }
}

void Ranging::onMousePressed(int x,int y)
{
    final_x=x;
    final_y=y;
}

void Ranging::setHighlightColor(Point3D &p)
{
    glLoadIdentity();

     //set size to 1 for a group of points
     glPointSize(10);

     //group #1 starts here
     glBegin(GL_POINTS);

        //color of group #1 is white
        glColor3f(0,1,0);

      //  for(int a=0; a<x; a++)
        //    for(int b=0; b<y; b++)
     glVertex3f(p.x,p.y,p.z);   //location of points
     glEnd();
}


