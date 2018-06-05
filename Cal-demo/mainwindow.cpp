#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->cancelBtn->setEnabled(false);
    ui->okBtn->setEnabled(false);
    ui->printBtn->setEnabled(false);
    ui->saveBtn->setEnabled(false);
    ui->border1->setStyleSheet("border:1px solid #b2b2b2;border-radius:2px;");
    this->setFixedSize(647,356);
    this->setWindowTitle(tr("实验一 随机误差的评定及计算"));
    connect(ui->clearBtn,SIGNAL(clicked(bool)),this,SLOT(slot_clear_inputs()));
    connect(ui->calBtn,SIGNAL(clicked(bool)),this,SLOT(slot_cal()));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::input_into_array()
{
    unsigned char i=0;
    inputArray[i++] = ui->inputLabel1->text().toFloat();
    inputArray[i++] = ui->inputLabel2->text().toFloat();
    inputArray[i++] = ui->inputLabel3->text().toFloat();
    inputArray[i++] = ui->inputLabel4->text().toFloat();
    inputArray[i++] = ui->inputLabel5->text().toFloat();
    inputArray[i++] = ui->inputLabel6->text().toFloat();
    inputArray[i++] = ui->inputLabel7->text().toFloat();
    inputArray[i++] = ui->inputLabel8->text().toFloat();
    inputArray[i++] = ui->inputLabel9->text().toFloat();
    inputArray[i++] = ui->inputLabel10->text().toFloat();
}

void MainWindow::slot_cal()
{
    input_into_array();
}

void MainWindow::slot_clear_inputs()
{
    ui->inputLabel1->clear();
    ui->inputLabel2->clear();
    ui->inputLabel3->clear();
    ui->inputLabel4->clear();
    ui->inputLabel5->clear();
    ui->inputLabel6->clear();
    ui->inputLabel7->clear();
    ui->inputLabel8->clear();
    ui->inputLabel9->clear();
    ui->inputLabel10->clear();
}
