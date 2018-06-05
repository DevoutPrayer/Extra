#include "socket.h"
#include <QDebug>
Socket::Socket()
{
    connect(this,SIGNAL(disconnected()),this,SLOT(slot_disConn()));
    connect(this,SIGNAL(readyRead()),this,SLOT(slot_readData()));
}

void Socket::slot_disConn()
{
    emit signal_disConn(this->socketDescriptor());
}

void Socket::slot_readData()
{
    //qDebug()<<x++;
    QDataStream in(this);
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    if(datasize==0)
    {
        if(bytesAvailable()<sizeof(quint32))
            return;
        in>>datasize;
        qDebug()<<datasize;
    }
    if(datasize > bytesAvailable())
        return;
    QString type;
    QString order;
    in>>type;
    in>>order;
    qDebug()<<"type="<<type<<";order="<<order;
    emit signal_peerMsg(type,order);
    datasize = 0;
}

void Socket::send_data(QString type, QString order)
{
    QByteArray dataStr;
    QByteArray dataStr1;
    QDataStream out(&dataStr,QIODevice::ReadWrite);
    QDataStream out1(&dataStr1,QIODevice::ReadWrite);
    out1.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out<<datasize;
    //qDebug()<<size;
    out<<type;
    //qDebug()<<dataStr.size();
    out<<order;
    //qDebug()<<dataStr.size();
    datasize = dataStr.size()-4;
    //qDebug()<<dataStr.size();
    out1<<datasize;
    //qDebug()<<dataStr.size();
    out1<<type;
    out1<<order;
    this->write(dataStr1);
    qDebug()<<"type="<<type<<";order="<<order;
    qDebug()<<"dataStr = "<<dataStr.size()<<";datasize = "<<datasize;
    //qDebug()<<dataStr;
    datasize=0;
}
