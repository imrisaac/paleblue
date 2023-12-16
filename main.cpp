// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

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

#include "settingsmanager.h"
#include "qtbuttonimageprovider.h"
#include "imageitem.h"
#include "paleblue.h"
#include "timemanager.h"


// Note: C++ main() is optional! You can alternatively run the qml on the command line:
// $ qml photosurface.qml -- /path/to/my/images

int main(int argc, char* argv[])
{
    QImageReader::setAllocationLimit(5500);
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    SettingsManager settingsManager;
    qmlRegisterSingletonInstance("com.isaac.SettingsManager", 1, 0, "SettingsManager", &settingsManager);

    qmlRegisterType<ImageItem>("com.isaac.imageitem", 1, 0, "ImageItem");
    QGuiApplication app(argc, argv);
    QCoreApplication::setApplicationName(QStringLiteral("Photosurface"));
    QCoreApplication::setOrganizationName(QStringLiteral("QtProject"));
    QCoreApplication::setApplicationVersion(QLatin1String(QT_VERSION_STR));

    QtButtonImageProvider imageProvider;
    QQmlApplicationEngine engine;

    TimeManager timeManager; // Create an instance of the TimeManager
    engine.addImageProvider("QtButton", &imageProvider);
    engine.rootContext()->setContextProperty("timeManager", &timeManager);
    engine.addImportPath("qrc:/qt/qml/photosurface/NetworkSettings");
    engine.load(QUrl("qrc:/qt/qml/photosurface/photosurface.qml"));

    if (engine.rootObjects().isEmpty())
        return -1;

    PaleBlue pale_blue(&engine);
    pale_blue.Run();



    return app.exec();
}

#include "main.moc"
