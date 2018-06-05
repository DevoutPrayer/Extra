#include "mainwindow.h"
#include "socket.h"
#include <QDebug>
#include <QTcpServer>
MainWindow::MainWindow()
{
    mainLayout = new QGridLayout(this);

    m_listWidget = new QListWidget;
    mainLayout->addWidget(m_listWidget,0,0,1,3);

    portLabel = new QLabel(tr("port:"));
    portLineEdit = new QLineEdit;
    ipLabel = new QLabel(tr("ip"));
    ipLineEdit = new QLineEdit;
    connBtn = new QPushButton(tr("connect"));
    mainLayout->addWidget(portLabel,1,0);
    mainLayout->addWidget(portLineEdit,1,1);
    mainLayout->addWidget(ipLabel,2,0);
    mainLayout->addWidget(ipLineEdit,2,1);
    mainLayout->addWidget(connBtn,3,2);
    socket = new Socket;
    tcpServer = new TcpServer;
    connect(socket,SIGNAL(connected()),this,SLOT(slot_conn()));
    connect(connBtn,SIGNAL(clicked(bool)),this,SLOT(slot_clickBtn()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(slot_disconn()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(slot_dataReceived()));
    connect(tcpServer,SIGNAL(signal_upMsg(QString,int)),this,SLOT(slot_upMsg(QString,int)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::slot_clickBtn()
{
    QString str,ip,port;
    ip = ipLineEdit->text();
    port = portLineEdit->text();
    qDebug()<<ip;
    qDebug()<<port;
    socket->connectToHost(ip,port.toInt());
    socket->waitForConnected();
}

void MainWindow::slot_conn()
{
    QString str;
    str = "连接成功！";
    m_listWidget->addItem(str);
}

void MainWindow::slot_disconn()
{
    QString str;
    str = "连接断开！";
    m_listWidget->addItem(str);
}

void MainWindow::slot_dataReceived()
{
    QString msg;
    while(socket->bytesAvailable()>0)
    {
        int length = socket->bytesAvailable();
        char buf[1024];
        socket->read(buf,length);
        msg = buf;
        QString tem;
        tem = msg.left(length);
        m_listWidget->addItem(tem);
        if(tem.contains("!"))
        {
            stringx += tem;
            if(stringx.contains("server"))
            {
                toBeServer();
                stringx = "";
            }
            else
            {
                QString stringy;
                int portstrpos = stringx.indexOf('y');
                int ipstrpos = stringx.indexOf('x');
                int endstrpos = stringx.indexOf('!');
                m_listWidget->addItem(tr("x")+QString::number(ipstrpos)+tr("y")+QString::number(portstrpos)+tr("!")+QString::number(endstrpos));
                ip = stringx.mid(ipstrpos+1).left(portstrpos-ipstrpos-1);
                stringy =  stringx.mid(portstrpos+1).left(endstrpos-portstrpos-1);
                m_listWidget->addItem("stringy="+stringy);
                port = stringy.toInt();
                toBeClient();
                stringx = "";
            }
        }
        else
            stringx += tem;
    }

}

void MainWindow::toBeServer()
{
    m_listWidget->addItem(tr("进入服务器模式！"));
    if(tcpServer->listenPort(socket->localPort()))

        m_listWidget->addItem(tr("监听端口成功！"));
}

void MainWindow::toBeClient()
{
    m_listWidget->addItem(tr("进入客户端模式！"));
    m_listWidget->addItem(ip);
    m_listWidget->addItem(QString::number(port));
    socket->close();
    socket->connectToHost(ip,port);
    socket->waitForConnected();
}

void MainWindow::slot_upMsg(QString str, int length)
{
    m_listWidget->addItem(str.left(length));
}
