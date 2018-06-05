#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    port = 8080;
    setWindowTitle(tr("TCPIPServer"));
    TempLabel1 = new QLabel(tr("当前温度"));
    TempLabel1_ = new QLabel();
    ContentListWidget = new QListWidget;
    PortLabel = new QLabel;
    PortLabel->setText(tr("端口号码："));
    PortLineEdit = new QLineEdit;
    PortLineEdit->setText(QString::number(port));
    CreateBtn = new QPushButton;
    CreateBtn->setText(tr("建立服务器"));
    MysqlConnectBtn = new QPushButton(tr("连接MySql数据库"));
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(TempLabel1,0,0);
    mainLayout->addWidget(TempLabel1_,0,1);
    mainLayout->addWidget(ContentListWidget,1,0,1,2);
    //mainLayout->addWidget(PortLabel,2,0);
//    mainLayout->addWidget(PortLineEdit,2,1);
    mainLayout->addWidget(CreateBtn,3,0,1,2);
    mainLayout->addWidget(MysqlConnectBtn,4,0,1,2);
    connect(CreateBtn,SIGNAL(clicked(bool)),this,SLOT(slotCreateServer()));
    connect(MysqlConnectBtn,SIGNAL(clicked(bool)),this,SLOT(slotMySqlConnect()));
}

Widget::~Widget()
{

}

void Widget::slotCreateServer()
{
    QString str ="--正在建立服务器-Port--";
    str+= QString::number(port);
    tcpServer = new TcpServer(this,port);
    emit slotUpdateList(str);
    connect(tcpServer,SIGNAL(updateServer(QString,int)),this,SLOT(updateServer(QString,int)));
    connect(tcpServer,SIGNAL(updateList(QString)),this,SLOT(slotUpdateList(QString)));
    CreateBtn->setEnabled(false);
}

void Widget::updateServer(QString msg, int length)
{
    //ContentListWidget ->addItem(msg.left(length-1));
    TempLabel1_->setText(msg.left(length-1).mid(5));
}

void Widget::slotUpdateList(QString msg)
{
    ContentListWidget->addItem(msg);
}

void Widget::slotMySqlConnect()
{
    mySqlConnect = new MySqlConnect;

    MysqlConnectBtn->setEnabled(false);
}
