#include "threaddisplay.h"
#include <QDebug>
ThreadDisplay::ThreadDisplay()
{

}

void ThreadDisplay::run()
{
    m_chart = new Chart;
    qDebug()<<"8899";
    this->exec();
}
