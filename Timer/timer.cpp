#include "timer.h"
#include <QDebug>

Timer::Timer(QWidget *parent)
    : QLCDNumber(parent)
{
    //设置一个没有面板边框和标题栏的窗体并且保证在最上层
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);

    //设置定时器背景颜色为蓝色
    QPalette p = palette();
    p.setColor(QPalette::Window,Qt::white);
    setPalette(p);

    //设置电子时钟半透明显示
    setWindowOpacity(0.5);

    //重新设置大小
    resize(150,60);

    DevoutPrayer_Timer *timer  = new DevoutPrayer_Timer;
    connect(timer,SIGNAL(signal_current_time(QString)),this,SLOT(slot_show_time(QString)));
}

Timer::~Timer()
{

}
void Timer::slot_show_time(QString text)
{
    if(showColon)
    {
        text[2] = ':';
        showColon = false;
    }
    else
    {
        text[2] = ' ';
        showColon = true;
    }
    display(text);
}

void Timer::mousePressEvent(QMouseEvent * event)
{
    if(event->button()==Qt::LeftButton)
    {
        dragPostion = event->globalPos()-frameGeometry().topLeft();
        event->accept();
    }
    else if(event->button()==Qt::RightButton)
    {
        close();
    }
}
void Timer::mouseMoveEvent(QMouseEvent * event)
{
    if(event->buttons()&Qt::LeftButton)
    {
        move(event->globalPos()-dragPostion);
        event->accept();
    }
}
