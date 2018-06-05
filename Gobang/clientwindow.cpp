#include "clientwindow.h"

ClientWindow::ClientWindow()
{
    /*初始化设置*/
    setAttribute(Qt::WA_DeleteOnClose);
    mainLayout = new QGridLayout(this);
    this->setWindowTitle("Client Panel");
    this->setFixedSize(400,400);
    socket = new Socket;
    /*标题*/
    QLabel *m_label = new QLabel(tr("Client Panel for Gobang"));
    m_label->setFont(QFont("Microsoft YaHei",20,10,1));
    mainLayout->addWidget(m_label,0,0,1,2,Qt::AlignHCenter);
    /*窗口*/
    m_listWidget = new QListWidget;
    mainLayout->addWidget(m_listWidget,1,0,1,2);
    /*服务器IP*/
    m_label = new QLabel(tr("Server ip:"));
    m_label->setFont(QFont("Microsoft YaHei",13,9,0));
    mainLayout->addWidget(m_label,2,0);
    ipLineEdit = new QLineEdit;
    ipLineEdit->setFont(QFont("Microsoft YaHei",13,9,0));
    ipLineEdit->setStyleSheet("color:blue");
    mainLayout->addWidget(ipLineEdit,2,1);
    /*端口*/
    m_label = new QLabel(tr("Server port:"));
    m_label->setFont(QFont("Microsoft YaHei",13,9,0));
    mainLayout->addWidget(m_label,3,0);
    portLineEdit = new QLineEdit;
    portLineEdit->setFont(QFont("Microsoft YaHei",13,9,0));
    portLineEdit->setStyleSheet("color:blue");
    mainLayout->addWidget(portLineEdit,3,1);
    /*开始按钮*/
    connBtn = new QPushButton(tr("connect"));
    connBtn->setFont(QFont("Microsoft YaHei",10,9,0));
    mainLayout->addWidget(connBtn,4,0,1,2,Qt::AlignRight);
    /*信号和槽*/
    connect(connBtn,SIGNAL(clicked(bool)),this,SLOT(slot_conn()));
    connect(socket,SIGNAL(signal_peerMsg(QString,QString)),this,SLOT(slot_peerMsg(QString,QString)));
}

void ClientWindow::slot_conn()
{
    if(isConn)
    {
        socket->close();
        connBtn->setText(tr("connect"));
        portLineEdit->setEnabled(true);
        ipLineEdit->setEnabled(true);
        slot_upMsg(tr("Disconnect from server."));
    }
    else
    {
        socket->connectToHost(ipLineEdit->text(),portLineEdit->text().toInt());
        if(socket->waitForConnected())
        {
            connBtn->setText(tr("disconnect"));
            portLineEdit->setEnabled(false);
            portLineEdit->setEnabled(false);
            slot_upMsg(tr("Connect to server!"));
        }
        else
        {
            slot_upMsg(tr("Connect failed!Plz check."));
        }
    }
}

void ClientWindow::slot_peerMsg(QString type, QString order)
{
    if(type.toInt()<17&&type.toInt()>0&&order.toInt()<17&&order.toInt()>0)
    {
        QString  peermsg;
        peermsg = "Peer chess position("+type+","+order+")";
        slot_upMsg(peermsg);
        emit signal_peerChessGo(type.toInt(),order.toInt());

    }
    else
    {
        QString  peermsg;
        peermsg = "Peer chess position("+type+","+order+")";
        slot_upMsg(peermsg);
        socket->send_data(tr("last"),"");
    }

}

void ClientWindow::slot_chessGo(int x,int y)
{
    socket->send_data(QString::number(x),QString::number(y));
    QString peermsg;
    peermsg = "Local chess position("+QString::number(x)+","+QString::number(y)+")";
    slot_upMsg(peermsg);
}

ClientWindow::~ClientWindow()
{
    emit signal_close();
}

void ClientWindow::slot_upMsg(QString msg)
{
    m_listWidget->addItem(msg);
    m_listWidget->scrollToBottom();
}
