#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H
#include <QTcpSocket>

class ServerSocket : public QTcpSocket
{
    Q_OBJECT
public:
    ServerSocket();
signals:
    void signal_disconn(int);
private slots:
    void slot_readdata();
    void slot_disconn();
};

#endif // SERVERSOCKET_H
