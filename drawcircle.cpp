#include "drawcircle.h"

DrawCircle::DrawCircle(QObject *parent) : QObject(parent)
{

}

bool DrawCircle::running() const
{
    return m_running;
}

void DrawCircle::run()
{
    while (m_running) {
        this->thread()->msleep(10);
        emit redraw();
    }

    emit finished();
}

void DrawCircle::setRunning(bool running)
{
    if (m_running == running)
        return;

    m_running = running;
    emit runningChanged(running);
}
