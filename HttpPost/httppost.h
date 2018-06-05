#ifndef HTTPPOST_H
#define HTTPPOST_H
#include <QByteArray>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class Httppost
{
public:
    Httppost();
private:
    QByteArray *postArray;
    QNetworkRequest *_request;
    QNetworkAccessManager *_manager;

};

#endif // HTTPPOST_H
