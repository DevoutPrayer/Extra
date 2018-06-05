#include "server.h"
#include <QDebug>
Server::Server()
{
    isConn = false;
}

bool Server::listen_port(int port)
{
    if(listen(QHostAddress::Any,port))
        return true;
    else
        return false;
}

void Server::incomingConnection(int sockDes)
{
    isConn = true;
    qDebug()<<"收到连接";
    serverSocket = new ServerSocket;
    serverSocket->setSocketDescriptor(sockDes);
    //QImage img;
    //img.load(":/logo.png");
}
void Server::sendImg(QImage img)
{
    qDebug()<<"发送图片";
    QBuffer buffer;
    QByteArray dataStr;
    QDataStream out(&dataStr,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    buffer.open(QIODevice::ReadWrite);
    img.save(&buffer,"PNG");
    out<<qint32(buffer.size())<<QString("2333")<<buffer.data();
    qDebug()<<buffer.size();
    serverSocket->write(dataStr);
    serverSocket->waitForBytesWritten();
}
