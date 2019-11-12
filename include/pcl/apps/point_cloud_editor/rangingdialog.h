#pragma once
#include <QDialog>
#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include <QWidget>
#include <pcl/apps/point_cloud_editor/cloud.h>

class RangingDialog:public QWidget{
    Q_OBJECT
public:
    RangingDialog(QWidget *mwidget=nullptr);
    ~RangingDialog();

    void ShowDialog(QString point1str,QString point2str,QString result);
private:
    QDialog *dialog;
    QPushButton *button;
    QVBoxLayout *layout;
    QLabel *point1label;
    QLabel *point2label;
    QLabel *result;
private slots:
    void btnClicked();
};
