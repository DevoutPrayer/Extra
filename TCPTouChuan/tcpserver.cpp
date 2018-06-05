#include "tcpserver.h"
#include <QDebug>

TCPServer::TCPServer()
{
}

bool TCPServer::listen_port(int port)
{
    QString str;
    if(this->isListening())
        this->close();
    if(this->listen(QHostAddress::Any,port))
    {
        str = "监听成功-Port:";
        str += QString::number(port);
        emit signal_upMsg(str,str.length());
        return true;
    }
    else
    {
        str = "监听失败-Port:";
        str += QString::number(port);
        emit signal_upMsg(str,str.length());
        return false;
    }
}



void TCPServer::incomingConnection(int socketDescriptor)
{
    QString str;
    str = "接受到一个连接--";
    qDebug()<<"接受到一个连接"<<socketDescriptor;
    str += QString::number(socketDescriptor);
    emit signal_upMsg(str,str.length());
    struct clients client;
    TcpSocket *tcpSocket = new TcpSocket;
    connect(tcpSocket,SIGNAL(signal_data(QString,int)),this,SLOT(slot_getmessage(QString,int)));
    connect(tcpSocket,SIGNAL(signal_disconn(int)),this,SLOT(slot_disConn(int)));
    tcpSocket->setSocketDescriptor(socketDescriptor);
    client.ip = tcpSocket->get_ip().mid(7);
    str = "ip地址--";
    str += client.ip;
    emit signal_upMsg(str,str.length());
    qDebug()<<client.ip;
    client.port = tcpSocket->get_port();
    str = "port--";
    str += QString::number(client.port);
    qDebug()<<client.port;
    emit signal_upMsg(str,str.length());
    client.tcpSocket = tcpSocket;
    clientList.append(client);
    if(clientList.count()==2)
    {
        QString str;
        str = "server!";
        clientList.at(0).tcpSocket->write(str.toLatin1(),str.toLatin1().length());
        clientList.at(0).tcpSocket->waitForBytesWritten();
        str = "client";
        str += "x";
        str += clientList.at(0).ip;
        str += "y";
        str += QString::number(clientList.at(0).port);
        str += "!";
        clientList.at(1).tcpSocket->write(str.toLatin1(),str.toLatin1().length());
        clientList.at(0).tcpSocket->waitForBytesWritten();
        str = "客户端连接数量为2";
        emit signal_upMsg(str,str.length());
    }
}

void TCPServer::slot_disConn(int socketDescriptor)
{
    QString str;
    str = "一个客户端断开连接--";
    for(int i = 0;i<clientList.count();i++)
    {
        if(clientList.at(i).tcpSocket->socketDescriptor()==socketDescriptor)
        {
            clientList.removeAt(i);
            str+= QString::number(socketDescriptor);
        }
    }
}

void TCPServer::slot_getmessage(QString string, int length)
{
    qDebug()<<string.left(length);
    emit signal_upMsg(string,length);
}
