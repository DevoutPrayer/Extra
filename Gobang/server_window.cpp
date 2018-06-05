#include "server_window.h"

ServerWindow::ServerWindow(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    /*初始化设置*/
    tcpServer = new TcpServer;
    this->isListening = false;
    this->setWindowTitle("Server Panel");
    this->setFixedSize(400,400);
    mainLayout = new QGridLayout(this);
    /*标题*/
    QLabel *m_label = new QLabel(tr("Server Panel for Gobang"));
    m_label->setFont(QFont("Microsoft YaHei",20,10,1));
    mainLayout->addWidget(m_label,0,0,1,2,Qt::AlignHCenter);
    /*服务器连接客户端数量*/
    m_label = new QLabel(tr("xxx"));
    m_label->setFont(QFont("Microsoft YaHei",13,9,0));
    connLabel = new QLabel(tr("7"));
    connLabel->setFont(QFont("Microsoft YaHei",13,9,0));
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::blue);
    connLabel->setPalette(pe);
    mainLayout->addWidget(m_label,1,0);
    mainLayout->addWidget(connLabel,1,1);
    /*已经连接的用户*/
    m_listWidget = new QListWidget;
    mainLayout->addWidget(m_listWidget,2,0,1,2);
    /*当前服务器IP*/
    m_label = new QLabel(tr("Server ip:"));
    m_label->setFont(QFont("Microsoft YaHei",13,9,0));
    ipLabel = new QLabel("127.0.0.1");
    ipLabel->setFont(QFont("Microsoft YaHei",13,9,0));
    ipLabel->setPalette(pe);
    mainLayout->addWidget(m_label,3,0);
    mainLayout->addWidget(ipLabel,3,1);
    /*监听端口*/
    m_label = new QLabel(tr("Listen Port:"));
    m_label->setFont(QFont("Microsoft YaHei",13,9,0));
    portLineEdit = new QLineEdit;
    portLineEdit->setFont(QFont("Microsoft YaHei",13,9,0));
    portLineEdit->setStyleSheet("color:blue");
    mainLayout->addWidget(m_label,4,0);
    mainLayout->addWidget(portLineEdit,4,1);
    /*开始按钮*/

    serStartBtn = new QPushButton(tr("Listen"));
    serStartBtn->setFont(QFont("Microsoft YaHei",10,9,0));
    mainLayout->addWidget(serStartBtn,5,0,1,1,Qt::AlignRight);
    sendBtn = new QPushButton(tr("xxx"));
    sendBtn->setEnabled(false);
    mainLayout->addWidget(sendBtn,5,1,1,1);
    /*信号和槽*/
    connect(serStartBtn,SIGNAL(clicked(bool)),this,SLOT(slot_serStartBtnClick()));
    connect(sendBtn,SIGNAL(clicked(bool)),this,SLOT(slot_conn()));
    connect(tcpServer,SIGNAL(signal_upMsg(QString)),this,SLOT(slot_upMsg(QString)));
    connect(tcpServer,SIGNAL(signal_peerMsg(QString,QString)),this,SLOT(slot_peerMsg(QString,QString)));
    connect(tcpServer,SIGNAL(signal_clientConn()),this,SLOT(slot_clientConn()));
}

ServerWindow::~ServerWindow()
{
    emit signal_close();
}

void ServerWindow::slot_conn()
{
    Socket *socket = new Socket;
    socket->connectToHost("127.0.0.1",18888);
}

void ServerWindow::slot_peerMsg(QString type, QString order)
{
    QString  peermsg;
    peermsg = "Peer chess position("+type+","+order+")";
    slot_upMsg(peermsg);
    if(type == "last")
    {
        slot_ChessGo(lastGo.x(),lastGo.y());
    }
    else
        emit signal_peerChessGo(type.toInt(),order.toInt());
}

void ServerWindow::slot_clientConn()
{
    emit signal_canGo();
    qDebug()<<"服务器走";
}

void ServerWindow::slot_ChessGo(int x,int y)
{
    lastGo.setX(x);
    lastGo.setY(y);
    tcpServer->send_data(QString::number(x),QString::number(y));
    QString  peermsg;
    peermsg = "Local chess position("+QString::number(x)+","+QString::number(y)+")";
    slot_upMsg(peermsg);
}

void ServerWindow::slot_serStartBtnClick()
{
    if(isListening)
    {
        tcpServer->close();
        serStartBtn->setText(tr("listen"));
        portLineEdit->setEnabled(true);
        isListening = false;
        slot_upMsg(tr("Stop listening port."));
    }
    else
    {
        if(tcpServer->listen(QHostAddress::Any,portLineEdit->text().toInt()))
        {
            qDebug()<<portLineEdit->text().toInt();
            serStartBtn->setText(tr("unListen"));
            portLineEdit->setEnabled(false);
            isListening = true;
            slot_upMsg(tr("Begin to listen port!"));
        }
        else
        {
            QMessageBox::critical(this,tr("Listen failed!"),tr("Listen failed!Plz check!"));
            return;
        }
    }
}

void ServerWindow::slot_upMsg(QString msg)
{
    m_listWidget->addItem(msg);
    m_listWidget->scrollToBottom();
}
