#include "mainwindow.h"

MainWindow::MainWindow()
{
    isListen = false;
    mainLayout = new QGridLayout(this);
    m_listWidget = new QListWidget();
    mainLayout->addWidget(m_listWidget,0,0,1,2);

    port_lineEdit = new QLineEdit;
    mainLayout->addWidget(port_lineEdit,1,0);

    listenBtn = new QPushButton;
    listenBtn->setText(tr("开始监听"));
    mainLayout->addWidget(listenBtn,1,1);
    tcpServer = new TCPServer;
    connect(listenBtn,SIGNAL(clicked(bool)),this,SLOT(slot_listenBtnClicked()));
    connect(tcpServer,SIGNAL(signal_upMsg(QString,int)),this,SLOT(slot_upMsg(QString,int)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::slot_listenBtnClicked()
{
    if(isListen)
    {
        tcpServer->close();
        listenBtn->setText(tr("开始监听"));
        port_lineEdit->setEnabled(true);
        isListen = false;
    }
    else
    {
        QString text;
        text = port_lineEdit->text();
        tcpServer->listen_port(text.toInt());
        listenBtn->setText(tr("停止监听"));
        port_lineEdit->setEnabled(false);
        isListen = true;
    }
}

void MainWindow::slot_upMsg(QString string, int length)
{
    m_listWidget->addItem(string.left(length));
}
