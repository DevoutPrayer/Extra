#include "MySqlConnect.h"

MySqlConnect::MySqlConnect()
{
    QString str = "MYSQL";
    QSqlDatabase qSqlDatabase = QSqlDatabase::addDatabase(str);
    qSqlDatabase.setHostName("123.206.50.248");
    qSqlDatabase.setPort(3309);
    qSqlDatabase.setDatabaseName("MySql");
    qSqlDatabase.setUserName("Discuz");
    qSqlDatabase.setPassword("Discuz");
    if(qSqlDatabase.open())
        emit UpdateList("success");
    else
        emit UpdateList("failed");
}
