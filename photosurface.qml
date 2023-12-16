// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause
import QtCore
import QtQuick
import QtQuick.Controls

import "resources"
import com.isaac.imageitem 1.0
import com.isaac.SettingsManager 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
//    width: Screen.width
//    height: Screen.height
    width: 400
    height: 400
    title: "Paleblue"

    // Function to crop a QImage
    function cropImage(sourceImage, cropRect) {
        // Create a copy of the source image and crop it
        var croppedImage = sourceImage.copy(cropRect);

        return croppedImage;
    }

    SwipeView {
        id: view

        currentIndex: 1
        anchors.fill: parent

        Item {
            id: firstPage
            Rectangle {
                anchors.fill: parent
                color: "black"

                ImageItem {
                    id: goes_east
                    objectName: "image_item_goes_east"
                    anchors.centerIn: parent
                    source: "https://cdn.star.nesdis.noaa.gov/GOES16/ABI/FD/GEOCOLOR/10848x10848.jpg"

                    width: Math.min(mainWindow.width, mainWindow.height)
                    height: Math.min(mainWindow.width, mainWindow.height)

                }
            }
        }
        Item {
            id: secondPage
            Rectangle {
                anchors.fill: parent
                color: "black"

                ImageItem {
                    id: goes_west
                    objectName: "image_item_goes_west"
                    anchors.centerIn: parent
                    source: "https://cdn.star.nesdis.noaa.gov/GOES18/ABI/FD/GEOCOLOR/10848x10848.jpg"

                    width: Math.min(mainWindow.width, mainWindow.height)
                    height: Math.min(mainWindow.width, mainWindow.height)
                }
            }
        }
        Item {
            id: thirdPage
            Rectangle {
                anchors.fill: parent


                Row {
                    id: buttonRow
                    anchors.top: panel.bottom
                    anchors.horizontalCenter: panel.horizontalCenter
                    spacing: buttonSize / 4
                    padding: buttonSize / 4
                    property var buttonSize: panel.height / 2

                    Text {
                        id: clockText
                        anchors.centerIn: parent
                        font.pixelSize: 40
                        color: "black"

                        // Use the currentTime property from the TimeManager
                        text: timeManager.currentTime
                    }
                    WifiButton {
                        id: wifiButton
                        height: parent.buttonSize
                        width: height
                        visible: true
                        onPressed: {
                            loader.source = "qrc:/NetworkSettings/NetworkSettingsPage.qml"
                        }
                    }
                }
            }
            Loader {
                id: loader
                anchors.fill: parent
            }
        }
        Item {
            id: fourthPage
            Rectangle {
                anchors.fill: parent
                color: "black"

                ImageItem {
                    id: goes_southeast
                    objectName: "image_item_goes_southeast"
                    anchors.centerIn: parent

                    width: Math.min(mainWindow.width, mainWindow.height)
                    height: Math.min(mainWindow.width, mainWindow.height)
                }

//                Connections {
//                    target: goes_east
//                    onImageChanged: {
//                        console.log("image changed in other image")
//                        var cropRect = Qt.rect(1000, 1000, 100, 800)
//                        goes_southeast.image = cropImage(goes_east.image, cropRect)
//                    }
//                }
            }
        }
    }
    PageIndicator {
        id: indicator

        count: view.count
        currentIndex: view.currentIndex

        anchors.bottom: view.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
