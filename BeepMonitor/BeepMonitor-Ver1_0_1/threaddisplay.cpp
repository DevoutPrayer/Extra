#include "threaddisplay.h"
#include <QDebug>
ThreadDisplay::ThreadDisplay(QChartView *chartView)
{
    qDebug()<<QThread::currentThreadId();
    m_chartView = chartView;
}

void ThreadDisplay::run()
{
    //sleep(1000);
    m_chart = new Chart(m_chartView);
    //qDebug()<<"8899";
    qDebug()<<QThread::currentThreadId();
    this->exec();
}
