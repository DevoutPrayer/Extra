#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QObject>

#include "socket.h"

class ClientWindow : public QWidget
{
    Q_OBJECT
public:
    ClientWindow();
    ~ClientWindow();
private:
    QGridLayout *mainLayout;
    QLineEdit *ipLineEdit;
    QLineEdit *portLineEdit;
    QPushButton *connBtn;
    QListWidget *m_listWidget;
    Socket *socket;
    bool isConn = false;
signals:
    void signal_close();
    void signal_canGo();
    void signal_peerChessGo(int,int);
public slots:
    void slot_chessGo(int,int);
    void slot_peerMsg(QString,QString);
private slots:
    void slot_conn();
    void slot_upMsg(QString);

};

#endif // CLIENTWINDOW_H
