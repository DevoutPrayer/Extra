#ifndef HTTPPOST_H
#define HTTPPOST_H

#include <QObject>
#include <QByteArray>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

class HttpPost : public QObject
{
    Q_OBJECT
public:
    HttpPost();
private slots:
    void slotHttpSend(QByteArray *postArray);
private:
    QNetworkAccessManager *_manager;
    QNetworkRequest *_request;
};

#endif // HTTPPOST_H
