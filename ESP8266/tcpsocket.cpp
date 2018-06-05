#include "tcpsocket.h"

TCPSocket::TCPSocket()
{
    connect(this,SIGNAL(readyRead()),this,SLOT(slot_dataRec()));
    connect(this,SIGNAL(disconnected()),this,SLOT(slot_disconnected()));
}

void TCPSocket::slot_dataRec()
{
    while(bytesAvailable()>0)
    {
        int length = bytesAvailable();
        char buf[1024];
        read(buf,length);
        QString msg = buf;
        emit signal_trmsg(msg,length,this->socketDescriptor());
    }
}

void TCPSocket::slot_disconnected()
{
    emit signal_disconn(this->socketDescriptor());
}
