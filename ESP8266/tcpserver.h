#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <QTcpServer>
#include <QObject>
#include "tcpsocket.h"

class TCPServer : public QTcpServer
{
    Q_OBJECT
public:
    TCPServer();
private:
    QList<TCPSocket*> clientList;
    void incomingConnection(int socketDescriptor);
public slots:
    void slot_semsg(QString,int);
private slots:
    void slot_disconn(int);
    void slot_trmsg(QString,int,int);
};

#endif // TCPSERVER_H
