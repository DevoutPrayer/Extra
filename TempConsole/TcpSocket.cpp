#include "TcpSocket.h"

TcpSocket::TcpSocket()
{
    //当套接字准备接收数据之时触发dataReceived();
    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));
    //当套接字断开连接时出发slotDisconnected();
    //个人认为套接字断开必须为主动断开，异常断开并不会触发
    connect(this,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
}

void TcpSocket::dataReceived()
{
    while(bytesAvailable()>0)
    {
        int length = bytesAvailable();
        char buf[1024];
        read(buf,length);
        QString msg = buf;
        emit updateClients(msg,length);
    }
}

void TcpSocket::slotDisconnected()
{
    emit disconnected(this->socketDescriptor());
}
