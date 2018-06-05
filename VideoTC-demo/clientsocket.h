#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H
#include <QTcpSocket>
#include <QDataStream>
#include <QImage>

class ClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    ClientSocket();
    bool connect_server(QString,int);
signals:
    void upPic(QImage);
private slots:
    void slot_readData();
private:
    qint32 dataSize;
    QString filename;
    QImage img;
};

#endif // CLIENTSOCKET_H
