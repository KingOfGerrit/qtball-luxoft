#include "dbservice.h"

DBService::DBService()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE", "mainDB");
    if(!QFile("qt_ball.db").exists()) {
        m_db.setDatabaseName("qt_ball.db");
        m_db.open();
        createInitDB();
        addInitData();
    }
    else {
        m_db.setDatabaseName("qt_ball.db");
        m_db.open();
    }
}

QSqlQuery DBService::selectAllData(QString table)
{
    QSqlQuery query(m_db);
    query.exec("SELECT * FROM " + table);
    return query;
}

void DBService::createInitDB()
{
    QSqlQuery query(m_db);
    query.exec("CREATE TABLE `coord` ( \
               `id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE, \
               `x`	INTEGER NOT NULL, \
               `y`	INTEGER NOT NULL, \
               `isUp`	INTEGER NOT NULL)"
            );
}

void DBService::addInitData()
{
   QSqlQuery query(m_db);
   query.prepare("INSERT INTO coord (x, y, isUp) VALUES (:x, :y, :isUp)");
   query.bindValue(":x", 150);
   query.bindValue(":y", 60);
   query.bindValue(":isUp", 1);
   query.exec();
}

DBService::~DBService()
{
    QString connection = m_db.connectionName();
    m_db.close();
    m_db = QSqlDatabase();
    QSqlDatabase::removeDatabase(connection);
}

void DBService::updateData(QPoint point, bool isUp)
{
    QSqlQuery query(m_db);
    query.prepare("UPDATE coord SET x = :x, y = :y, isUp = :isUp WHERE id = 1");
    query.bindValue(":x", point.x());
    query.bindValue(":y", point.y());
    query.bindValue(":isUp", isUp ? 1 : 0);
    query.exec();
}
