#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QByteArray>
#include <QString>
#include <QLabel>
#include "httppost.h"
#include "TcpServer.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
private:
    HttpPost *httpPost;
    QByteArray *postArray;
    TcpServer *tcpServer;
signals:
    postSthServer(QByteArray *);
public slots:
    void slotUpdateServer(QString,int);
    void slotUpdateList(QString);
};

#endif // WIDGET_H
