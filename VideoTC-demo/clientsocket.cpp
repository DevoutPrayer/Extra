#include "clientsocket.h"
#include <QDebug>
ClientSocket::ClientSocket()
{
    dataSize = 0;
    connect(this,SIGNAL(readyRead()),this,SLOT(slot_readData()));
    //img.load(":/logo.png");
    //qDebug()<<"执行信号函数";
    //emit upPic(img);
}

bool ClientSocket::connect_server(QString ip,int port)
{
    connectToHost(ip,port);
    if(waitForConnected())
        return true;
    else
        return false;
}

void ClientSocket::slot_readData()
{
    QDataStream in(this);
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    if(dataSize ==0)
    {
        if(bytesAvailable() < (sizeof(quint32)+sizeof(QString)))
            return;
        in >> dataSize;
        in >> filename;
    }
    if(dataSize > qint32(bytesAvailable()))
        return;
    QByteArray a;
    in >> a;
    img.loadFromData(a);
    qDebug()<<dataSize;
    qDebug()<<filename;
    dataSize = 0;
    emit upPic(img);
}
