#ifndef TCPSOCKET_H
#define TCPSOCKET_H
#include <QTcpSocket>
#include <QObject>
class TCPSocket : public QTcpSocket
{
    Q_OBJECT
public:
    TCPSocket();
signals:
    void signal_trmsg(QString,int,int);
    void signal_disconn(int);
protected slots:
    void slot_dataRec();
    void slot_disconnected();
};

#endif // TCPSOCKET_H
