// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause
import QtCore
import QtQuick
import QtQuick.Controls

import "resources"

ApplicationWindow {
    id: mainWindow
    visible: true
    width: Screen.width
    height: Screen.height
    title: "Full-Screen Image Viewer"

    Rectangle {
        anchors.fill: parent
        color: "black"

        Image {
            id: imageViewer
            anchors.centerIn: parent
            source: "resources/10848x10848.jpg"
            fillMode: Image.PreserveAspectFit

            width: Math.min(mainWindow.width, mainWindow.height)
            height: Math.min(mainWindow.width, mainWindow.height)
        }
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Escape) {
            mainWindow.close()
        }
    }
}
