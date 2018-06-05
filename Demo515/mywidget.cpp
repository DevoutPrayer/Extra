#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QGridLayout;
    this->setLayout(mainLayout);
    closePushBtn = new QPushButton("Close");
    mainLayout->addWidget(closePushBtn,0,0,1,1,Qt::AlignHCenter);
    connect(closePushBtn,&QPushButton::clicked,this,&MyWidget::slotClose);
}
void MyWidget::slotClose()
{
    emit signalShow();
    this->close();
}
