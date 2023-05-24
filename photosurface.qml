// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause
import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import Qt.labs.folderlistmodel
import "resources"

pragma ComponentBehavior: Bound

Window {
    id: root
    visible: true
//    visibility: "FullScreen"
    width: 1080; height: 1080
    color: "black"
    title: Application.displayName + " : " + folderModel.folder
    property real defaultSize: 200
    property real surfaceViewportRatio: 1
    property var imageNameFilters: ["*.png", "*.jpg", "*.gif"] // overridden in main.cpp

    FolderDialog {
        id: folderDialog
        title: qsTr("Choose a folder with some images")
        onAccepted: folderModel.folder = selectedFolder
    }

    ScrollView {
        id: flick
        anchors.fill: parent
        contentWidth: width * root.surfaceViewportRatio
        contentHeight: height * root.surfaceViewportRatio
        property int highestZ: 0
        Repeater {
            model: FolderListModel {
                id: folderModel
                objectName: "folderModel"
                showDirs: false
                nameFilters: root.imageNameFilters

            }
            delegate: Rectangle {
                required property string fileModified
                required property string fileName
                required property string fileUrl
                id: photoFrame
                objectName: "frame-" + fileName
                width: image.width
                height: image.height
                scale: root.defaultSize / Math.max(image.sourceSize.width, image.sourceSize.height)
//                border.color: pinchHandler.active || dragHandler.active ? "darkturquoise"
//                                                                        : mouse.hovered ? "darkseagreen"
//                                                                                        : "saddlebrown"
                border.width: 3
                antialiasing: true
                Component.onCompleted: {
                    x = Math.random() * root.width - width / 2
                    y = Math.random() * root.height - height / 2
                    rotation = Math.random() * 13 - 6
                }

                Image {
                    id: image
                    anchors.centerIn: parent
                    fillMode: Image.PreserveAspectFit
                    source: photoFrame.fileUrl
                    antialiasing: true
                }

//                Text {
//                    text: fileName + " ❖ " + Qt.formatDateTime(fileModified, Locale.LongFormat)
//                    horizontalAlignment: Text.AlignHCenter
//                    elide: Text.ElideRight
//                    font.pixelSize: (parent.height - image.height) / 3
//                    anchors {
//                        left: parent.left
//                        right: parent.right
//                        bottom: parent.bottom
//                        margins: font.pixelSize / 5
//                    }
//                }

                MomentumAnimation {
                    id: anim
                    target: photoFrame
                    onFinished: {
                        flick.contentWidth = Math.max(photoFrame.x + photoFrame.width, flick.contentWidth)
                        flick.contentHeight = Math.max(photoFrame.y + photoFrame.height, flick.contentHeight)
                    }
                }

                PinchHandler {
                    id: pinchHandler
                    minimumRotation: -360
                    maximumRotation: 360
                    minimumScale: 0.01
                    maximumScale: 5
                    grabPermissions: PointerHandler.CanTakeOverFromAnything // and never gonna give it up
                    onActiveChanged: if (active) photoFrame.z = ++flick.highestZ
                }

                DragHandler {
                    id: dragHandler
                    onActiveChanged: {
                        if (active)
                            photoFrame.z = ++flick.highestZ
                        else
                            anim.restart(centroid.velocity)
                    }
                }

                HoverHandler { id: mouse }

                WheelHandler {
                    acceptedModifiers: Qt.ControlModifier
                    property: "rotation"
                    onActiveChanged: if (active) photoFrame.z = ++flick.highestZ
                }

                WheelHandler {
                    acceptedModifiers: Qt.ShiftModifier
                    property: "scale"
                    onActiveChanged: {
                        if (active) photoFrame.z = ++flick.highestZ
                        console.log(scale)
                    }
                }

                TapHandler{
                    onActiveChanged: console.log("tappy tap tap")
                    onTapped: console.log("tappy tap tap")
                    onDoubleTapped: {
                        console.log("double tappy tap")
                        photoFrame.scale = 1080/photoFrame.width
                        photoFrame.x = flick.contentWidth / 2
                        photoFrame.y = flick.contentHeight / 2
                        photoFrame.rotation = 0
                    }
                }

            }
        }
    }

    Image {
        anchors.top: parent.top
        anchors.left: parent.center
        source: "resources/folder.png"

        TapHandler { onTapped: folderDialog.open() }

        HoverHandler { id: folderMouse }

        ToolTip.visible: folderMouse.hovered
        ToolTip.text: qsTr(`Open an image directory (${openShortcut.nativeText})`)
        ToolTip.delay: 1000

        Shortcut {
            id: openShortcut
            sequence: StandardKey.Open
            onActivated: folderDialog.open()
        }
    }

//    Text {
//        anchors.bottom: parent.bottom
//        anchors.left: parent.left
//        anchors.right: parent.right
//        anchors.margins: 10
//        color: "darkgrey"
//        wrapMode: Text.WordWrap
//        font.pointSize: 8
//        text: qsTr(`On a touchscreen: use two fingers to zoom and rotate, one finger to drag
//                  \nWith a mouse: drag and scroll normally, shift-wheel to zoom, control-wheel to rotate`)
//    }

    Shortcut { sequence: StandardKey.Quit; onActivated: Qt.quit() }

    Component.onCompleted: {
        const lastArg = Application.arguments.slice(-1)[0]
        const standardPicturesLocations = StandardPaths.standardLocations(StandardPaths.PicturesLocation)
        const hasValidPicturesLocation = standardPicturesLocations.length > 0
        if (hasValidPicturesLocation)
            folderDialog.currentFolder = standardPicturesLocations[0]
        if (/.*hotosurface.*|--+/.test(lastArg)) {
            if (hasValidPicturesLocation)
                folderModel.folder = standardPicturesLocations[0]
            else
                folderDialog.open()
        }
        else
            folderModel.folder = Qt.resolvedUrl("file:" + lastArg)

        flick.contentY = flick.contentHeight / 2 - height / 2
        flick.contentX = flick.contentWidth / 2 - width / 2
    }
}
