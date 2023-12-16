#include "timemanager.h"
#include <QDateTime>

TimeManager::TimeManager(QObject *parent) : QObject(parent)
{
    connect(&m_timer, &QTimer::timeout, this, &TimeManager::updateCurrentTime);
    m_timer.start(1000); // Update the time every second (1000 ms)

    // Initialize the currentTime property with the current time
    updateCurrentTime();
}

QString TimeManager::currentTime() const
{
    return m_currentTime;
}

void TimeManager::updateCurrentTime()
{
    m_currentTime = QDateTime::currentDateTime().toString("HH:mm:ss");
    emit timeUpdated();
}
