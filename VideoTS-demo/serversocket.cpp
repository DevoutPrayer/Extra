#include "serversocket.h"

ServerSocket::ServerSocket()
{
    connect(this,SIGNAL(readyRead()),this,SLOT(slot_readdata()));
    connect(this,SIGNAL(disconnected()),this,SLOT(slot_disconn()));
}

void ServerSocket::slot_readdata()
{

}

void ServerSocket::slot_disconn()
{
    emit signal_disconn(this->socketDescriptor());
}
