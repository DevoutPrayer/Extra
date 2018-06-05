#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include "tcpsocket.h"

struct clients
{
    TcpSocket *tcpSocket;
    QString ip;
    int port;
};

class TCPServer : public QTcpServer
{
public:
    TCPServer();
    bool listen_port(int);
private:
    int port;
    QList<clients> clientList;
signals:
    void signal_upMsg(QString,int);
public slots:
    void slot_disConn(int);
    void slot_getmessage(QString,int);
protected:
    void incomingConnection(int);
};

#endif // TCPSERVER_H
