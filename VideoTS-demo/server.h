#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QBuffer>
#include <QImage>
#include "serversocket.h"
class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    bool listen_port(int);
    void incomingConnection(int sockDes);
    void sendImg(QImage);
    bool isConn;
private:
    ServerSocket *serverSocket;
};

#endif // SERVER_H
