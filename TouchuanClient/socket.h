#ifndef SOCKET_H
#define SOCKET_H
#include <QTcpSocket>

class Socket : public QTcpSocket
{
    Q_OBJECT
public:
    Socket();
};

#endif // SOCKET_H
