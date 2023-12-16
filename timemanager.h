#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <QObject>
#include <QTimer>

class TimeManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentTime READ currentTime NOTIFY timeUpdated)

public:
    explicit TimeManager(QObject *parent = nullptr);

    QString currentTime() const;

signals:
    void timeUpdated();

private slots:
    void updateCurrentTime();

private:
    QTimer m_timer;
    QString m_currentTime;
};

#endif // TIMEMANAGER_H
