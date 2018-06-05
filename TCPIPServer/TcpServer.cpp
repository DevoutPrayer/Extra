#include "TcpServer.h"

TcpServer::TcpServer(QObject *parent,int port) : QTcpServer(parent)
{
    if(listen(QHostAddress::Any,port)==0)
    {
        QString str ="--监听端口成功--port--";
        str += QString::number(port);
        emit updateList(str);
    }
    else{
        QString str ="--监听端口失败--port--";
        str += QString::number(port);
        emit updateList(str);
    }

}

void TcpServer::incomingConnection(int socketDescriptor)
{
    TcpSocket *tcpSocket = new TcpSocket();
    connect(tcpSocket,SIGNAL(updateClients(QString,int)),this,SLOT(updateClients(QString,int)));
    connect(tcpSocket,SIGNAL(disconnected(int)),this,SLOT(slotDisconnected(int)));
    tcpSocket->setSocketDescriptor(socketDescriptor);

    tcpClientList.append(tcpSocket);
    QString str = "--接受到一个连接-socketDescriptor--";
    str+= QString::number(socketDescriptor);
    emit updateList(str);
}

void TcpServer::updateClients(QString msg, int length)
{
    emit updateServer(msg,length);
}

void TcpServer::slotDisconnected(int descriptor)
{
    for(int i=0;i<tcpClientList.count();i++)
    {
        QTcpSocket *item = tcpClientList.at(i);
        if(item->socketDescriptor()==descriptor)
        {
            QString str ="--设备断开连接--socketDescriptor--";
            str += QString::number(descriptor);
            emit updateList(str);
            tcpClientList.removeAt(i);
            return;
        }
    }
    return;
}
