#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbservice.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_point = calc.point();

    ui->setupUi(this);

    m_spyThread = new QSignalSpy(&calc, SIGNAL(finished()));

    connect(&threadCalc, &QThread::started, &calc, &Calculate::run);
    connect(&threadDraw, &QThread::started, &drawCircle, &DrawCircle::run);

    connect(&calc, &Calculate::sendPoint, this, &MainWindow::setPoint, Qt::DirectConnection);
    connect(&drawCircle, &DrawCircle::redraw, this, &MainWindow::redraw);
    //connect(this, SIGNAL(pointChanged(QPoint)), this, SLOT(repaint()));

    connect(&calc, &Calculate::finished, &threadCalc, &QThread::quit, Qt::DirectConnection);
    connect(&drawCircle, &DrawCircle::finished, &threadDraw, &QThread::quit, Qt::DirectConnection);

    //connect(&threadCalc, &QThread::finished, &threadCalc, &QThread::deleteLater);
    //connect(&threadDraw, &QThread::finished, &threadDraw, &QThread::deleteLater);

    calc.moveToThread(&threadCalc);
    drawCircle.moveToThread(&threadDraw);
}

MainWindow::~MainWindow()
{
    calc.setRunning(false);
    drawCircle.setRunning(false);
    threadCalc.wait();
    threadDraw.wait();

    qDebug() << "Spy thread:" << m_spyThread->count();
    delete m_spyThread;

    DBService db;
    db.updateData(m_point, calc.isUp());

    delete ui;
}

QPoint MainWindow::point() const
{
    return m_point;
}

void MainWindow::setPoint(QPoint point)
{
    if (m_point == point)
        return;

    m_point = point;
    emit pointChanged(point);
}

void MainWindow::redraw()
{
    repaint();
}

void MainWindow::on_start_clicked()
{
    calc.setRunning(true);
    drawCircle.setRunning(true);
    threadCalc.start();
    threadDraw.start();
}

void MainWindow::on_stop_clicked()
{
    calc.setRunning(false);
    drawCircle.setRunning(false);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
    painter.drawEllipse(m_point, 50, 50);

}
