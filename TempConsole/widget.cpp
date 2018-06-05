#include "widget.h"
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    qDebug()<<1;
    tcpServer = new TcpServer(this,8080);
    httpPost = new HttpPost;
    postArray = new QByteArray;
    connect(tcpServer,SIGNAL(updateServer(QString,int)),this,SLOT(slotUpdateServer(QString,int)));
    connect(tcpServer,SIGNAL(updateList(QString)),this,SLOT(slotUpdateList(QString)));
    connect(this,SIGNAL(postSthServer(QByteArray*)),httpPost,SLOT(slotHttpSend(QByteArray *)));
 //   postArray->append("text=778888888");
   // emit postSthServer(postArray);
}

Widget::~Widget()
{

}
void Widget::slotUpdateList(QString string)
{
    qDebug()<<string;
}
void Widget::slotUpdateServer(QString string, int length)
{
    qDebug()<<string.left(length-1).mid(5);
    postArray->clear();
    postArray->append("text="+string.left(length-1).mid(5));
    qDebug()<<postArray;
    emit postSthServer(postArray);
}
