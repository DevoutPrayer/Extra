#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>
#include <QImage>
#include "clientsocket.h"


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
public slots:
    void slot_refreshPic(QImage);
    void slot_timeout();
private:
    int fps;
    ClientSocket *clientSocket;
    QGridLayout *mainLayout;
    QLabel *m_label;
    QLabel *fpslabel;
    QLineEdit *ipLineEdit;
    QLineEdit *portLineEdit;
    QPushButton *startBtn;
    bool isConn;
private slots:
    void slot_start();
};

#endif // WIDGET_H
