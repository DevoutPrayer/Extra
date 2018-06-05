#ifndef TIMER_H
#define TIMER_H

#include <QLCDNumber>
#include <QMouseEvent>
#include "devoutprayer_timer.h"

class Timer : public QLCDNumber
{
    Q_OBJECT

public:
    Timer(QWidget *parent = 0);
    ~Timer();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
public slots:
    void slot_show_time(QString);
private:
    bool showColon = true;
    QPoint dragPostion;
};

#endif // TIMER_H
