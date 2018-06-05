#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <QTcpServer>

class TcpServer :public QTcpServer
{
    Q_OBJECT
signals:
    void signal_upMsg(QString,int);
public:
    TcpServer();
    bool listenPort(int);
protected:
    void incomingConnection(int s);
};

#endif // TCPSERVER_H
