#ifndef MYSQLCONNECT_H
#define MYSQLCONNECT_H
#include <QObject>
#include <QtSql/QSqlDatabase>

class MySqlConnect :   QObject
{
    Q_OBJECT
signals:
    void UpdateList(QString);
public:
    MySqlConnect();

};

#endif // MYSQLCONNECT_H
