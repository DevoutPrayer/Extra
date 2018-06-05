#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->m_chartView->setRenderHint(QPainter::Antialiasing);//抗锯齿
    threadDisplay = new ThreadDisplay(ui->m_chartView);
    //ui->m_chartView->moveToThread(threadDisplay);
    threadDisplay->start();
    //qDebug()<<m_chart->animationDuration();
}

MainWindow::~MainWindow()
{
    delete ui;
    threadDisplay->exit();
    threadDisplay->wait();
    threadDisplay->deleteLater();
}
/*
void MainWindow::handleTimeOut()
{
    static bool isTurn = true;
    static bool isFull = false;
    static int x = 0;
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
}*/
