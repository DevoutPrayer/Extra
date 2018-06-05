#include "tcp_server.h"
#include<QDebug>
TcpServer::TcpServer()
{
    socket = new Socket;
    connect(socket,SIGNAL(signal_peerMsg(QString,QString)),this,SLOT(slot_peerMsg(QString,QString)));
}

void TcpServer::incomingConnection(int sockDes)
{
    qDebug()<<tr(("客户端连接。。"));
    socket->setSocketDescriptor(sockDes);
    emit signal_upMsg(tr("A client is connected."));
    emit signal_clientConn();
    isConn = true;
    //socket->send_data("17","18");
    //socket->send_data("17","18");
    //socket->waitForBytesWritten();

}

void TcpServer::send_data(QString type, QString order)
{
    if(isConn)
        socket->send_data(type,order);
}

void TcpServer::slot_peerMsg(QString type, QString order)
{
    emit signal_peerMsg(type,order);
}
