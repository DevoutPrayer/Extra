#include "mainwindow.h"

MainWindow::MainWindow()
{
    m_label = new QLabel;
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(m_label,0,0);
    drawPixMap();
}

MainWindow::~MainWindow()
{

}

void MainWindow::drawPixMap()
{
    QPixmap p;
    p.load(":/logo.png");
    m_label->setPixmap(p);
}
