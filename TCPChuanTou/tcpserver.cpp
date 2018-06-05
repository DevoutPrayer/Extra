#include "tcpserver.h"
#include <QDebug>

TCPServer::TCPServer()
{
}

bool TCPServer::listen_port(int port)
{
    if(this->isListening())
        this->close();
    if(this->listen(QHostAddress::Any,port))
    {
        return true;
    }
    else
        return false;
}



void TCPServer::incomingConnection(int socketDescriptor)
{
    qDebug()<<"接受到一个连接"<<socketDescriptor;
    struct clients client;
    TcpSocket *tcpSocket = new TcpSocket;
    connect(tcpSocket,SIGNAL(signal_data(QString,int)),this,SLOT(slot_getmessage(QString,int)));
    connect(tcpSocket,SIGNAL(signal_disconn(int)),this,SLOT(slot_disConn(int)));
    tcpSocket->setSocketDescriptor(socketDescriptor);
    client.ip = tcpSocket->get_ip();
    qDebug()<<client.ip;
    client.port = tcpSocket->get_port();
    qDebug()<<client.port;
    client.tcpSocket = tcpSocket;
    clientList.append(client);
}

void TCPServer::slot_disConn(int socketDescriptor)
{
    for(int i = 0;i<clientList.count();i++)
    {
        if(clientList.at(i).tcpSocket->socketDescriptor()==socketDescriptor)
        {
            clientList.removeAt(i);
        }
    }
}

void TCPServer::slot_getmessage(QString string, int length)
{
    qDebug()<<string.left(length);
    emit signal_upMsg(string,length);
}
