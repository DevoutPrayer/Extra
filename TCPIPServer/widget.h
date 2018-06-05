#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include "TcpServer.h"
#include "MySqlConnect.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
private:
    QListWidget *ContentListWidget;
    QLabel *TempLabel1;
    QLabel *TempLabel1_;
    QLabel *PortLabel;
    QLineEdit *PortLineEdit;
    QPushButton *CreateBtn;
    QPushButton *MysqlConnectBtn;
    QGridLayout *mainLayout;
    int port;
    TcpServer *tcpServer;
    MySqlConnect *mySqlConnect;
public slots:
    void slotCreateServer();
    void updateServer(QString,int);
    void slotUpdateList(QString);
    void slotMySqlConnect();
};

#endif // WIDGET_H
