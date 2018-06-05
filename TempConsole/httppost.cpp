#include "httppost.h"

HttpPost::HttpPost()
{
    _request = new QNetworkRequest;
    _manager = new QNetworkAccessManager;
}
void HttpPost::slotHttpSend(QByteArray *postArray)
{
    _request->setUrl(QUrl("http://www.heuev.cn/temp.php"));
    _request->setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    _request->setHeader(QNetworkRequest::ContentLengthHeader,postArray->size());
    _manager->post(*_request,*postArray);
}
