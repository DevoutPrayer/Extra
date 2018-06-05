#include "widget.h"
#include "tcpserver.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //设置主窗口
    this->setWindowIcon(QIcon(":/logo.ico"));
    this->setWindowTitle(tr("ESP8266上位机--By HeXiao"));
    this->setFixedWidth(380);
    m_font = QFont("宋体",11,2,false);
    //网格视图
    mainLayout = new QGridLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    //QListWidget
    list = new QListWidget;
    list->setFixedSize(380,400);
    mainLayout->addWidget(list,0,0,1,3,Qt::AlignHCenter);
    //QHBoxLayout
    m_HLayout = new QHBoxLayout;
    mainLayout->addLayout(m_HLayout,1,1,1,3,Qt::AlignHCenter);
    //QLabel
    m_label = new QLabel;
    m_label->setText(tr("监听端口号"));
    m_label->setFont(m_font);
    //m_label->setFixedSize(100,20);
    //m_label->setStyleSheet("margin:0;border:1px solid red;");
    m_HLayout->addWidget(m_label,1,Qt::AlignLeft);
    //QLineEdit
    portLineEdit = new QLineEdit;
    //portLineEdit->setFixedSize(100,20);
    portLineEdit->setFont(m_font);
    //portLineEdit->setStyleSheet("margin-left:0;");
    m_HLayout->addWidget(portLineEdit,1,Qt::AlignLeft);
    //QPushButton
    submitBtn = new QPushButton;
    submitBtn->setText(tr("提交"));
    //submitBtn->setFixedSize(60,20);
    //submitBtn->setStyleSheet("border-radius:2px;");
    m_HLayout->addWidget(submitBtn,1,Qt::AlignLeft);
    TCPServer *tcpServer = new TCPServer;
    connect(submitBtn,SIGNAL(clicked(bool)),this,SLOT(slot_submit()));
    connect(this,SIGNAL(signal_semsg(QString,int)),tcpServer,SLOT(slot_semsg(QString,int)));
}


Widget::~Widget()
{

}

void Widget::slot_submit()
{
    QString str;
    int length;
    if(portLineEdit->text()!=""&&portLineEdit->text()!=NULL)
    {
        str = portLineEdit->text();
        length = portLineEdit->text().length();
        emit signal_semsg(str,length);
    }
}
