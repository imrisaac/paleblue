#ifndef PALEBLUE_H
#define PALEBLUE_H

#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickWindow>
#include <QtGui/QGuiApplication>
#include <QtGui/QImageReader>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QMimeDatabase>
#include <QtCore/QStandardPaths>
#include <QtCore/QUrl>
#include <QTime>
#include <QTimer>

#include "filedownloader.h"

class Helper: public QObject{
    Q_OBJECT
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)
public:
    QImage image() const{ return m_image; }
    void setImage(const QImage &image){
        if(m_image == image)
            return;
        m_image = image;
        emit imageChanged();
    }
signals:
    void imageChanged();
private:
    QImage m_image;
};

class PaleBlue: public QObject{
    Q_OBJECT
public:
    PaleBlue(QQmlApplicationEngine *engine);
    bool Init();
    bool Run();

private:
    FileDownloader *m_file_downloader;
    QObject *m_east;
    QObject *m_west;
    QObject *m_southeast;

private slots:
    void GetImage(QUrl imageUrl, Helper *helper);
    void GoesEastImageChanged();
    void GoesWestImageChanged();
};

#endif // PALEBLUE_H
