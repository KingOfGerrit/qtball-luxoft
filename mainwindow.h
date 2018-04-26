#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "calculate.h"
#include "drawcircle.h"

#include <QMainWindow>
#include <QThread>
#include <QPainter>
#include <QFile>
#include <string>
#include <QSignalSpy>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(QPoint point READ point WRITE setPoint NOTIFY pointChanged)

    Ui::MainWindow *ui;

    QThread threadCalc;
    QThread threadDraw;
    Calculate calc;
    DrawCircle drawCircle;

    QPoint m_point;

    QSignalSpy *m_spyThread;

    void paintEvent(QPaintEvent *event);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPoint point() const;

public slots:
    void setPoint(QPoint point);
    void redraw();

signals:
    void pointChanged(QPoint point);

private slots:
    void on_start_clicked();
    void on_stop_clicked();

};

#endif // MAINWINDOW_H
