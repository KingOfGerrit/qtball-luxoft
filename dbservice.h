#ifndef DBSERVICE_H
#define DBSERVICE_H

#include <QtSql>

class DBService
{
public:
    explicit DBService();
    QSqlQuery selectAllData(QString table);
    ~DBService();
    void updateData(QPoint point, bool isUp);

private:
    QSqlDatabase m_db;
    void createInitDB();
    void addInitData();

signals:

public slots:
};

#endif // DBSERVICE_H
