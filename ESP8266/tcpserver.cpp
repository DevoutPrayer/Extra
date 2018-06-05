#include "tcpserver.h"
#include <QTimer>
#include <QDateTime>

TCPServer::TCPServer()
{
    if(listen(QHostAddress::Any,14888))
       qDebug()<<"监听成功！";
}

void TCPServer::incomingConnection(int socketDescriptor)
{
    TCPSocket *tcpSocket = new TCPSocket;
    connect(tcpSocket,SIGNAL(signal_trmsg(QString,int,int)),this,SLOT(slot_trmsg(QString,int,int)));
    connect(tcpSocket,SIGNAL(signal_disconn(int)),this,SLOT(slot_disconn(int)));
    tcpSocket->setSocketDescriptor(socketDescriptor);
    qDebug()<<"一个客户端已经连接！";
    clientList.append(tcpSocket);
}

void TCPServer::slot_trmsg(QString str, int length, int sockId)
{
    QString str1;
    str1 = "8899";
    qDebug()<<"收到:"<<sockId<<":::"<<str.left(length);
}
void TCPServer::slot_disconn(int socketId)
{
    for(int i=0;i<clientList.count();i++)
    {
        TCPSocket *tcpSocket = clientList.at(i);
        if(tcpSocket->socketDescriptor()==socketId)
        {
            clientList.removeAt(i);
            return;
        }
    }
}
void TCPServer::slot_semsg(QString str, int length)
{
    QByteArray array;
    array.append(str.left(length));
    for(int i=0;i<clientList.count();i++)
    {
        TCPSocket *tcpSocket = clientList.at(i);
        tcpSocket->write(array,array.length());
    }
}
