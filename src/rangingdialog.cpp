#include <pcl/apps/point_cloud_editor/rangingdialog.h>
#include <QObject>

RangingDialog::RangingDialog(QWidget *widget){
    dialog=new QDialog(widget);
    point1label=new QLabel(dialog);
    point2label=new QLabel(dialog);
    result=new QLabel(dialog);
    dialog->setWindowTitle("测量距离结果");
    button=new QPushButton(dialog);
    button->setText("确定");
    layout=new QVBoxLayout();
    layout->addWidget(point1label);
    layout->addWidget(point2label);
    layout->addWidget(result);
    layout->addWidget(button);
    dialog->setLayout(layout);
    connect(button,SIGNAL(clicked()),this,SLOT(btnClicked()));
}

RangingDialog::~RangingDialog(){}


void
RangingDialog::btnClicked()
{
    dialog->close();
}

void
RangingDialog::ShowDialog(QString point1str, QString point2str, QString resultstr)
{
    point1label->setText(point1str);
    point2label->setText(point2str);
    result->setText(resultstr);
    dialog->show();
}
