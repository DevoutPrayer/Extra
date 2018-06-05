#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    fps = 0;
    isConn = false;
    QTimer *timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(slot_timeout()));
    clientSocket = new ClientSocket;
    mainLayout = new QGridLayout(this);
    m_label = new QLabel;
    mainLayout->addWidget(m_label,0,0,1,2);
    fpslabel = new QLabel;
    mainLayout->addWidget(fpslabel,1,0,1,2);
    QLabel *label = new QLabel("ip:");
    mainLayout->addWidget(label,2,0,1,1);
    ipLineEdit = new QLineEdit;
    mainLayout->addWidget(ipLineEdit,2,1,1,1);
    label = new QLabel("port:");
    mainLayout->addWidget(label,3,0,1,1);
    portLineEdit= new QLineEdit;
    mainLayout->addWidget(portLineEdit,3,1,1,1);
    startBtn = new QPushButton(tr("开始"));
    mainLayout->addWidget(startBtn,4,0,1,2,Qt::AlignRight);
    connect(clientSocket,SIGNAL(upPic(QImage)),this,SLOT(slot_refreshPic(QImage)));
    connect(startBtn,SIGNAL(clicked(bool)),this,SLOT(slot_start()));
    timer->start(1000);
}

Widget::~Widget()
{

}

void Widget::slot_start()
{
    if(isConn)
    {
        portLineEdit->setEnabled(true);
        ipLineEdit->setEnabled(true);
        startBtn->setText(tr("开始"));
        clientSocket->close();
        isConn = false;
    }
    else
    {
        QString ip;
        int port;
        ip = ipLineEdit->text();
        port = portLineEdit->text().toInt();
        if(clientSocket->connect_server(ip,port))
        {
            portLineEdit->setEnabled(false);
            ipLineEdit->setEnabled(false);
            startBtn->setText(tr("停止"));
            isConn = true;
        }
    }

}

void Widget::slot_timeout()
{
    fpslabel->setText ( "fps:"+QString::number(fps));
    fps = 0;
}
void Widget::slot_refreshPic(QImage img)
{
    fps++;
    QPixmap p;
    p = p.fromImage(img);
    m_label->setPixmap(p);
}
