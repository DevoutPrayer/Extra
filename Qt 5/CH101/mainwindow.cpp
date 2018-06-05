#include "mainwindow.h"
#include "ui_mainwindow.h"
#define PI 3.1416
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    bool ok;
    QString tempStr;
    QString valueStr = ui->lineEdit->text();    //从文本框中读取字符串并存入QString类下的一个对象中
    int valueInt = valueStr.toInt(&ok);         //用的是QString 的一个方法toInt
    double area = valueInt*valueInt*PI;
    ui->label_3->setText(valueStr.setNum(area));//此处貌似用valueStr和tempStr好像没什么区别
}
