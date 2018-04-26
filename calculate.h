#ifndef CALCULATE_H
#define CALCULATE_H

#include <QObject>
#include <QThread>
#include <QtCore>

class Calculate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(QPoint point READ point WRITE setPoint NOTIFY pointChanged)

public:
    explicit Calculate(QObject *parent = 0);
    QPoint point() const;
    bool running() const;
    bool isUp() const;

signals:
    void finished();
    void sendPoint(QPoint point);
    void runningChanged(bool running);
    void pointChanged(QPoint point);

public slots:
    void run();
    void setRunning(bool running);
    void setPoint(QPoint point);

private:
    QPoint m_point;
    bool m_running;
    bool isUp_;

    void move();
    void readFile();
};

#endif // CALCULATE_H
