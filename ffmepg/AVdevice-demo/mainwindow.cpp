#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //qDebug()<<avcodec_configuration();
    //unsigned version = avcodec_version();
    //QString ch = QString::number(version,10);
    //qDebug()<<"version:"<<version;
    avdevice_register_all();
    avformat_alloc_context();
    //avformat_configuration();
    //AVFormatContext *pFormatCtx = avformat_alloc_context();
    //AVInputFormat *ifmt= av_find_input_format("vfwcap");
    //avformat_open_input(&pFormatCtx, 0, ifmt,NULL);
}

MainWindow::~MainWindow()
{
    delete ui;
}
