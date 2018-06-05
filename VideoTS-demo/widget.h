#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraImageCapture>
#include <QImage>
#include <QLabel>
#include <QGridLayout>
#include <QTimer>
#include "server.h"


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    Server *server;
    QCamera *m_camera;
    QCameraImageCapture *imageCap;
private:
    QGridLayout *mainLayout;
    QLabel *m_label;
public slots:
    void slot_sendPic(int,QImage);
    void slot_timeout();
};

#endif // WIDGET_H
