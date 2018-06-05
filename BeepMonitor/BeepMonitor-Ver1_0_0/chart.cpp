#include "chart.h"
#include <QDebug>
Chart::Chart(QObject *parent) : QObject(parent)
{
    m_timer = new QTimer;
    connect(m_timer,SIGNAL(timeout()),this,SLOT(handleTimeOut()));
    m_timer->start(1000);
}

void Chart::handleTimeOut()
{
    qDebug()<<"xxx";
}
