#include "calculate.h"
#include <QFile>
#include "dbservice.h"
#include <QDebug>

Calculate::Calculate(QObject *parent) : QObject(parent)
{
    readFile();
}

bool Calculate::running() const
{
    return m_running;
}

bool Calculate::isUp() const
{
    return isUp_;
}

QPoint Calculate::point() const
{
    return m_point;
}

void Calculate::run()
{
    while (m_running) {
        this->thread()->msleep(10);
        move();
        qDebug() << m_point;
        emit sendPoint(m_point);
    }

    emit finished();
}

void Calculate::setRunning(bool running)
{
    if (m_running == running)
        return;

    m_running = running;
    emit runningChanged(running);
}

void Calculate::setPoint(QPoint point)
{
    if (m_point == point)
        return;

    m_point = point;
    emit pointChanged(point);
}

void Calculate::move()
{
    if (isUp_) {
        m_point.setX(m_point.x() + 1);
        m_point.setY(m_point.y() + 1);
    }
    else {
        m_point.setX(m_point.x() - 1);
        m_point.setY(m_point.y() - 1);
    }

    if (m_point.y() == 250) {
        isUp_ = false;
    }
    if (m_point.y() == 60) {
        isUp_ = true;
    }
}

void Calculate::readFile()
{
    m_point.setX(150);
    m_point.setY(60);
    isUp_ = true;

    DBService db;
    QSqlQuery query = db.selectAllData("coord");
    QSqlRecord rec = query.record();
    while (query.next()) {
        m_point.setX(query.value(rec.indexOf("x")).toInt());
        m_point.setY(query.value(rec.indexOf("y")).toInt());
        isUp_ = query.value(rec.indexOf("isUp")).toBool();
    }

//    QFile file("position.txt");
//    if ((file.exists()) && (file.open(QIODevice::ReadOnly))) {
//        QRegExp rx("(\\ )");
//        QString line = file.readAll();
//        QStringList coordinates = line.split(rx);
//        if (coordinates.size() > 2) {
//            m_point.setX(coordinates.at(0).toInt());
//            m_point.setY(coordinates.at(1).toInt());
//            isUp_ = coordinates.at(2).toInt();
//        }

//        file.close();
//    }
}
