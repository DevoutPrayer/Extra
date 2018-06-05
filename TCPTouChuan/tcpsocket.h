#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpSocket>
#include <QHostAddress>

class TcpSocket :public QTcpSocket
{
    Q_OBJECT
public:
    TcpSocket();
    QString get_ip();
    quint16 get_port();
signals:
    void signal_data(QString,int);
    void signal_disconn(int);
protected slots:
    void dataReceived();
    void slotDisconnected();
};
#endif // TCPSOCKET_H
