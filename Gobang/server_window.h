#ifndef SERVER_WINDOW_H
#define SERVER_WINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>

#include "tcp_server.h"
#include "socket.h"

class ServerWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ServerWindow(QWidget *parent = 0);
    ~ServerWindow();
private:
    QGridLayout *mainLayout;
    QPushButton *serStartBtn;
    QLineEdit *portLineEdit;
    QListWidget *m_listWidget;
    QLabel *connLabel;
    QLabel *ipLabel;
    bool isListening;
    TcpServer *tcpServer;
    QPushButton *sendBtn;
    QPoint lastGo;
signals:
    void signal_close();
    void signal_canGo();
    void signal_peerChessGo(int,int);
public slots:
    void slot_upMsg(QString);
    void slot_ChessGo(int,int);
    void slot_peerMsg(QString,QString);
    void slot_clientConn();
private slots:
    void slot_serStartBtnClick();
    void slot_conn();

};

#endif // SERVER_WINDOW_H
