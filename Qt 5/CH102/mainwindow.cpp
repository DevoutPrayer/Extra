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

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
   bool ok;
   QString valueStr = ui->lineEdit->text();
   double valueInt = valueStr.toInt(&ok);
   double area = valueInt*valueInt*PI;
   ui->label_3->setText(valueStr.setNum(area));
}
