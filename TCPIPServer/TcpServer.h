#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <QTcpServer>
#include <QObject>
#include "TcpSocket.h"

class TcpServer :public QTcpServer
{
    Q_OBJECT
public:
    TcpServer(QObject *parent,int port);
    QList<TcpSocket*> tcpClientList;
signals:
    void updateServer(QString,int);
    void updateList(QString);
public slots:
    void updateClients(QString,int);
    void slotDisconnected(int);
protected:
    void incomingConnection(int socketDescriptor);
};

#endif // TCPSERVER_H
