#include "widget.h"
#include "workthread.h"
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    WorkThread *array[7];
    for(int i=0;i<7;i++)
    {
        array[i] = new WorkThread(&mutex);
        connect(array[i],SIGNAL(signal_finished()),this,SLOT(slot_delete()));
    }
    for(int i=0;i<7;i++)
        array[i]->start();
}

Widget::~Widget()
{

}
void Widget::slot_delete()
{
    qDebug()<<QString::fromLocal8Bit("一个线程退出！");
}
