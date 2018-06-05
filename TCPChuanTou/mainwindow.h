#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "tcpserver.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
private:
    QGridLayout *mainLayout;
    QLineEdit *port_lineEdit;
    QPushButton *listenBtn;
    QListWidget *m_listWidget;
    bool isListen;
    TCPServer *tcpServer;
private slots:
    void slot_listenBtnClicked();
public slots:
    void slot_upMsg(QString,int);
};

#endif // MAINWINDOW_H
