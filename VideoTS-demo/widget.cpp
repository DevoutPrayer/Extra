#include "widget.h"
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QTimer *timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(slot_timeout()));
    server = new Server;
    server->listen_port(18888);
    m_camera = new QCamera(QCameraInfo::defaultCamera());
    imageCap = new QCameraImageCapture(m_camera);
    imageCap->setCaptureDestination(QCameraImageCapture::CaptureToBuffer);
    m_camera->setCaptureMode(QCamera::CaptureStillImage);
    m_camera->start();
    mainLayout = new QGridLayout(this);
    m_label = new QLabel;
    mainLayout->addWidget(m_label,0,0);
    connect(imageCap,SIGNAL(imageCaptured(int,QImage)),this,SLOT(slot_sendPic(int,QImage)));
    timer->start(20);
}

Widget::~Widget()
{

}

void Widget::slot_timeout()
{
    imageCap->capture();
}

void Widget::slot_sendPic(int id,QImage img)
{
    qDebug()<<"图片";
    QPixmap p;
    p = p.fromImage(img);
    m_label->setPixmap(p);
    if(server->isConn)
    {
        server->sendImg(img);
    }

}
