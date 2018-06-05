#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    qsrand((uint) QTime::currentTime().msec());
    m_timer = new QTimer;
    connect(m_timer,SIGNAL(timeout()),this,SLOT(handleTimeOut()));
    mainLayout = new QGridLayout(this);
    m_chart = new QChart;
    m_axis = new QValueAxis;
    m_splineSeries = new QSplineSeries;
    m_chart->addSeries(m_splineSeries);
    m_splineSeries->append(1,2);
    m_splineSeries->append(3,7);
    m_splineSeries->append(5,4);
    m_splineSeries->append(7,2);
    m_chart->createDefaultAxes();
    m_chart->setAxisX(m_axis,m_splineSeries);
    m_chart->axisX()->setRange(0,20);
    m_chart->axisY()->setRange(-10,10);
    m_chartView = new QChartView;
    m_chartView->setChart(m_chart);
    m_chartView->setFixedSize(1200,200);
    m_chartView->setRenderHint(QPainter::Antialiasing);//设置抗锯齿
    mainLayout->addWidget(m_chartView,0,0);
    m_timer->start(1000);
}

Widget::~Widget()
{

}

void Widget::handleTimeOut()
{
    m_splineSeries->append(left+margin+width,qrand()%20-10);
    left += margin;
    m_chart->axisX()->setRange(left,left+width);

}
