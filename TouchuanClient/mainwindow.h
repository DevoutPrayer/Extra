#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include "socket.h"
#include "tcpserver.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
private:
    QListWidget *m_listWidget;
    QLabel *portLabel;
    QLabel *ipLabel;
    QLineEdit *portLineEdit;
    QLineEdit *ipLineEdit;
    QPushButton *connBtn;
    QGridLayout *mainLayout;
    Socket *socket;
    TcpServer *tcpServer;
    QString ip;
    QString stringx;
    int port;
    bool isServer;
    void toBeServer();
    void toBeClient();
private slots:
    void slot_clickBtn();
    void slot_conn();
    void slot_disconn();
    void slot_dataReceived();
    void slot_upMsg(QString,int);
};

#endif // MAINWINDOW_H
