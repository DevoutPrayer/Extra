#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->m_chartView->setRenderHint(QPainter::Antialiasing);//抗锯齿
    threadDisplay.start();
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    m_timer = new QTimer;
    m_chart = new QChart;
    m_axisX = new QValueAxis;
    m_axisY = new QValueAxis;
    m_splineSeries = new QSplineSeries;
    m_lineSeries1 = new QLineSeries;
    m_lineSeries2 = new QLineSeries;
    /*QChart初始化*/
    m_chart->legend()->hide();//隐藏图例
    //m_chart->setAnimationOptions(QChart::SeriesAnimations);//设置曲线呈动画显示
    //m_chart->addSeries(m_splineSeries);
    m_chart->addSeries(m_lineSeries1);
    m_chart->addSeries(m_lineSeries2);
    m_chart->setPlotAreaBackgroundBrush(QBrush(QColor("#000")));
    m_chart->setPlotAreaBackgroundVisible(true);
    /*QLinearGradient backgroundGradient;
    backgroundGradient.setStart(QPointF(0, 0));
    backgroundGradient.setFinalStop(QPointF(0, 1));
    backgroundGradient.setColorAt(0.0, QRgb(0xd2d0d1));
    backgroundGradient.setColorAt(1.0, QRgb(0x4c4547));
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    m_chart->setBackgroundBrush(backgroundGradient);
    QLinearGradient plotAreaGradient;
    plotAreaGradient.setStart(QPointF(0, 1));
    plotAreaGradient.setFinalStop(QPointF(1, 0));
    plotAreaGradient.setColorAt(0.0, QRgb(0x555555));
    plotAreaGradient.setColorAt(1.0, QRgb(0x55aa55));
    plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    m_chart->setPlotAreaBackgroundBrush(plotAreaGradient);
    m_chart->setPlotAreaBackgroundVisible(true);*/
    /*设置坐标轴*/
    m_axisX->setRange(0,200);
    //m_axisX->setTitleText(QString::fromLocal8Bit("X轴"));
    //m_axisX->setLabelFormat("%s");
    m_axisX->setTickCount(7);
    m_axisX->setMinorTickCount(4);
    m_axisX->setMinorGridLinePen(QPen(QColor("blue"),0.3,Qt::SolidLine));
    m_axisX->setGridLinePen(QPen(QColor("blue"),0.3,Qt::SolidLine));
    m_chart->setAxisX(m_axisX,m_lineSeries1);
    m_chart->setAxisX(m_axisX,m_lineSeries2);
    m_axisY->setRange(0,20);
    //m_axisY->setTitleText(QString::fromLocal8Bit("Y轴"));
    /*m_axisY->setShadesBrush(QBrush(QColor(0x99, 0xcc, 0xcc, 0x55)));
    m_axisY->setShadesVisible(true);*/
    m_chart->setAxisY(m_axisY,m_lineSeries1);
    m_chart->setAxisY(m_axisY,m_lineSeries2);


    //m_lineSeries->setPointLabelsClipping(false);
    //m_lineSeries->append(5,5);
    //m_lineSeries->append(6,7);
    m_lineSeries1->setPen(QPen(QColor("green"),1));
    m_lineSeries2->setPen(QPen(QColor("green"),1));
    m_lineSeries1->useOpenGL();
    m_lineSeries2->useOpenGL();


    ui->m_chartView->setChart(m_chart);

    connect(m_timer,SIGNAL(timeout()),this,SLOT(handleTimeOut()));
    m_timer->start(100);

    //qDebug()<<m_chart->animationDuration();
}

MainWindow::~MainWindow()
{
    delete ui;
    threadDisplay.exit();
    threadDisplay.wait();
    threadDisplay.deleteLater();
}

void MainWindow::handleTimeOut()
{
    /**/
    static bool isTurn = true;
    static bool isFull = false;
    static int x = 0;
    //-qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int y = qrand()%20;
    QPoint point(x,y);
    if(isFull)
    {
        if(isTurn)
        {
            lineSeries1List.append(point);
            if(lineSeries2List.count()>0)
            {
                m_lineSeries2->remove(lineSeries2List.at(0).x(),lineSeries2List.at(0).y());
                lineSeries2List.removeAt(0);
            }
            if(x>190)
            {
                m_lineSeries1->remove(lineSeries1List.at(0).x(),lineSeries1List.at(0).y());
                lineSeries1List.removeAt(0);
            }

            m_lineSeries1->append(x,y);
            if(x==200)
            {
                isTurn = !isTurn;
                x=-1;
            }
            x++;
        }
        else
        {
            lineSeries2List.append(point);
            if(lineSeries1List.count()>0)
            {
                m_lineSeries1->remove(lineSeries1List.at(0).x(),lineSeries1List.at(0).y());
                lineSeries1List.removeAt(0);
            }
            if(x>190)
            {
                m_lineSeries2->remove(lineSeries2List.at(0).x(),lineSeries2List.at(0).y());
                lineSeries2List.removeAt(0);
            }
            m_lineSeries2->append(x,y);
            if(x==200)
            {
                isTurn = !isTurn;
                x=-1;
            }
            x++;
        }
    }
    else
    {
        lineSeries1List.append(point);
        m_lineSeries1->append(x,y);
        if(x==190)
        {
            isFull = true;
            //x = -1;
        }
        x++;
    }
}
