#include "mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QGridLayout *mainLayout = new QGridLayout;
    QWidget *mWidget = new QWidget();
    this->setCentralWidget(mWidget);
    mWidget->setLayout(mainLayout);
    openPushBtn  = new QPushButton("Open");
    mainLayout->addWidget(openPushBtn,0,0,1,1,Qt::AlignHCenter);
    connect(openPushBtn,&QPushButton::clicked,this,&MainWindow::slot_openBtnClick);
}

MainWindow::~MainWindow()
{

}
void MainWindow::slot_openBtnClick()
{
    MyWidget *newWidget = new MyWidget;
    newWidget->setFixedSize(200,100);
    newWidget->show();

    this->hide();
    connect(newWidget,&MyWidget::signalShow,this,&MainWindow::slot_appear);
    //qDebug()<<"11";
}

void MainWindow::slot_appear()
{
    this->show();
    //qDebug()<<"22";
}
