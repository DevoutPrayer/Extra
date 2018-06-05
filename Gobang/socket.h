#ifndef SOCKET_H
#define SOCKET_H
#include <QTcpSocket>
#include <QDataStream>

class Socket : public QTcpSocket
{
    Q_OBJECT
public:
    Socket();
    void send_data(QString,QString);
signals:
    void signal_disConn(int);
    void signal_peerMsg(QString,QString);
private slots:
    void slot_disConn();
    void slot_readData();
private:
    quint32 datasize;
    quint32 x=0;
};

#endif // SOCKET_H
