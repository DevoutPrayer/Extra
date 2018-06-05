#include "tcpserver.h"

TcpServer::TcpServer()
{

}

bool TcpServer::listenPort(int port)
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

void TcpServer::incomingConnection(int s)
{
    QString str;
    str = "作为服务器一个客户端又连接了！";
    emit signal_upMsg(str,str.length());
}
