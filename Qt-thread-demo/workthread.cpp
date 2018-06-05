#include "workthread.h"
#include <QDebug>
WorkThread::WorkThread(QMutex *mutex_)
{
    mutex = new QMutex;
    mutex = mutex_;
    connect(this,SIGNAL(finished()),this,SLOT(slot_delete()));
    connect(this,SIGNAL(finished()),this,SLOT(deleteLater()));
}

void WorkThread::run()
{
    mutex->lock();
    for(int i=0;i<10;i++)
        qDebug()<<i<<i<<i<<i<<i<<i<<i<<i;
    mutex->unlock();
}

void WorkThread::slot_delete()
{
    emit signal_finished();
}
