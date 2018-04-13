#ifndef DRAWCIRCLE_H
#define DRAWCIRCLE_H

#include <QObject>
#include <QThread>

class DrawCircle: public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)

public:
    explicit DrawCircle(QObject *parent = 0);
    bool running() const;

public slots:
    void run();
    void setRunning(bool running);

signals:
    void finished();
    void redraw();
    void runningChanged(bool running);

private:
    bool m_running;
};

#endif // DRAWCIRCLE_H
