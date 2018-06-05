#ifndef TCP_SERVER_H
#define TCP_SERVER_H
#include <QTcpServer>
#include <socket.h>

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    TcpServer();
    void send_data(QString,QString);
private:
    Socket *socket;
    void incomingConnection(int sockDes);
    bool isConn = false;
signals:
    void signal_upMsg(QString);
    void signal_peerMsg(QString,QString);
    void signal_clientConn();
public slots:
    void slot_peerMsg(QString,QString);
};

#endif // TCP_SERVER_H
