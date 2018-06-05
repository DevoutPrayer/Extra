#include "httppost.h"
#include <QDebug>
#include <QString>
Httppost::Httppost()
{
    postArray = new QByteArray;
    postArray->append("text=7788");
    _request = new QNetworkRequest;
    _request->setUrl(QUrl(QString("http://www.heuev.cn/temp.php")));
    _request->setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    _request->setHeader(QNetworkRequest::ContentLengthHeader,postArray->size());
    _manager = new QNetworkAccessManager;
    _manager->post(*_request,*postArray);
    //_manager.get(QNetworkRequest(QUrl("http://123.206.50.248/temp.php")));
    //_manager = new QNetworkAccessManager;
    //QUrl url("http://www.heuev.cn/temp.php");
    //QNetworkReply* reply = _manager->get(QNetworkRequest(url));
    qDebug()<<"????";
}
