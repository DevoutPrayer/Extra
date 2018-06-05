#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include "tcpsocket.h"
#include <QObject>

struct clients
{
    TcpSocket *tcpSocket;
    QString ip;
    int port;
};

class TCPServer : public QTcpServer
{
    Q_OBJECT
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
