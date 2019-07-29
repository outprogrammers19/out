import QtQuick 2.9

import QtQuick.Controls 2.9

Item {
    id: settingsPage;

    Connections {
        target: manager;
        onUpdateFinished: {
            if (status === true)
                successStatus.visible = true;
            else
                failedStatus.visible = true;
        }
    }

    Rectangle {
        anchors.fill: parent;
        color: "white";
    }

    Flickable {
        anchors.fill: parent;
        contentHeight: settingsColumn.contentHeight;
        contentWidth: settingsPage.width;
        flickableDirection: Flickable.AutoFlickIfNeeded;

        ScrollBar.vertical: ScrollBar {
            property bool isScrollbarVisible: settingsColumn.contentHeight > settingsPage.height;
            id: scrollBar;
            width: Config.scrollbarWidth;
            policy: isScrollbarVisible ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff;
            anchors.right: parent.right;
        }

        Column {
            id: settingsColumn;
            anchors.fill: parent;
            width: settingsPage.width;
            property real contentHeight: 4 * Math.max(1, Math.floor(1 * Config.scale))
                                         + updatesRow.height
                                         + settingsRow.height
                                         + exitRow.height;

            Rectangle { // separator
                width: settingsPage.width;
                height: Math.max(1, Math.floor(1 * Config.scale));
                color: "lightgrey";
            }

            Rectangle { // Updates row
                id: updatesRow;
                width: settingsPage.width;
                height: 100 * Config.scale;

                Label {
                    id: updateLabel
                    text: "Updates:";
                    font.pixelSize: Config.bigFontSize;
                    font.bold: true;
                    x: 20 * Config.scale;
                    y: 20 * Config.scale;
                }

                Label {
                    font.pixelSize: Config.bigFontSize;
                    id: successStatus;
                    text: "Up-to-date";
                    color: "green";
                    anchors.left: updateLabel.right;
                    anchors.leftMargin: 6 * Config.scale;
                    y: 20 * Config.scale;
                    visible: false;
                }
                Label {
                    font.pixelSize: Config.bigFontSize;
                    id: failedStatus;
                    text: "Failed";
                    color: "red";
                    anchors.left: updateLabel.right;
                    anchors.leftMargin: 6 * Config.scale;
                    y: 20 * Config.scale;
                    visible: false;
                }

                Item {
                    height: parent.height;
                    anchors.centerIn: parent;
                    width: 400 * Config.scale;

                    Item {
                        id: busyIndicator;
                        width: 65 * Config.scale;
                        height: 65 * Config.scale;
                        anchors.verticalCenter: parent.verticalCenter;
                        anchors.right: updateButton.left;
                        anchors.rightMargin: 10 * Config.scale;

                        BusyIndicator { anchors.fill: parent; }

                        // There is some bug in BusyIndicator, so let's leave it always on and use a cover to show it
                        Rectangle {
                            id: indicatoCover;
                            anchors.fill: parent;
                            color: manager.isUpdating ? "transparent" : "white";
                        }
                    }

                    Button {
                        id: updateButton;
                        width: 140 * Config.scale;
                        height: Config.docEntryButtonHeight;
                        anchors.verticalCenter: parent.verticalCenter;
                        anchors.right: parent.right;
                        text: "Update";
                        font.pixelSize: Config.bigFontSize;
                        enabled: !manager.isUpdating;

                        hoverEnabled: true;
                        ToolTip.delay: 1000;
                        ToolTip.timeout: 5000;
                        ToolTip.visible: hovered;
                        ToolTip.text: "Check for updates and download if any exists.";

                        icon.source: "qrc:/other/view-refresh.png";
                        icon.height: height - 22 * Config.scale;
                        icon.width: width - 22 * Config.scale;
                        icon.color: enabled ? "black" : "lightgrey";

                        onReleased: {
                            successStatus.visible = false;
                            failedStatus.visible = false;
                            manager.update();
                        }
                    }
                }
            } // !Updates row

            Rectangle { // separator
                width: settingsPage.width;
                height: Math.max(1, Math.floor(1 * Config.scale));
                color: "lightgrey";
            }

            Rectangle { // Scale row
                id: settingsRow;
                width: settingsPage.width;
                height: 100 * Config.scale;

                Label {
                    id: scaleLabel;
                    text: "Interface Scale Factor:";
                    font.pixelSize: Config.bigFontSize;
                    font.bold: true;
                    x: 20 * Config.scale;
                    y: 10 * Config.scale;
                }
                Label {
                    text: slider.value.toFixed(2);
                    font.pixelSize: Config.bigFontSize;
                    anchors.left: scaleLabel.right;
                    anchors.leftMargin: 6 * Config.scale;
                    y: 10 * Config.scale;
                }
                Item {
                    anchors.centerIn: parent;
                    width: scaleRow.width + scaleButton.width;
                    height: parent.height;

                    Item { // Scale row
                        id: scaleRow;
                        height: 100 * Config.scale;
                        width: slider.width * slider.scale;

                        Slider {
                            id: slider;
                            y: 48 * Config.scale;
                            width: 120; // NOTE: do not multiply by Config.scale, you multiplied slider.scale
                            anchors.horizontalCenter: parent.horizontalCenter;
                            from: 0.75;
                            value: 1.0;
                            to: 2.0;
                            snapMode: Slider.SnapAlways;
                            stepSize: 0.25;
                            scale: 2.0 * Config.scale;
                        }
                    }
                    Button {
                        id: scaleButton;
                        width: 140 * Config.scale;
                        height: Config.docEntryButtonHeight;
                        text: "Apply";
                        font.pixelSize: Config.bigFontSize;
                        anchors.verticalCenter: scaleRow.verticalCenter;
                        anchors.left: scaleRow.right;
                        anchors.leftMargin: 10 * Config.scale;
                        enabled: slider.value !== Config.scale;

                        hoverEnabled: true;
                        ToolTip.delay: 1000;
                        ToolTip.timeout: 5000;
                        ToolTip.visible: hovered;
                        ToolTip.text: "Re-scale application with the new scale factor."

                        icon.source: "qrc:/other/view-fullscreen.png";
                        icon.height: height - 22 * Config.scale;
                        icon.width: height - 22 * Config.scale;
                        icon.color: enabled ? "black" : "lightgrey";

                        onReleased: {
                            Config.scale = slider.value;
                            manager.rescaled = true;
                        }
                    }
                }
            } // !Scale row

            Rectangle { // separator
                width: settingsPage.width;
                height: Math.max(1, Math.floor(1 * Config.scale));
                color: "lightgrey";
            }

            Rectangle { // Exit row
                id: exitRow;
                width: settingsPage.width;
                height: 100 * Config.scale;

                //            Label {
                //                id: exitLabel
                //                text: "Close the application:";
                //                font.pixelSize: Config.bigFontSize;
                //                font.bold: true;
                //                x: 20 * Config.scale;
                //                y: 20 * Config.scale;
                //            }

                Item {
                    height: parent.height;
                    anchors.centerIn: parent;
                    width: 400 * Config.scale;


                    Button {
                        id: exitButton;
                        width: 140 * Config.scale;
                        height: Config.docEntryButtonHeight;
                        anchors.verticalCenter: parent.verticalCenter;
                        anchors.right: parent.right;
                        text: " Exit ";
                        font.pixelSize: Config.bigFontSize;
                        enabled: !manager.isUpdating;

                        hoverEnabled: true;
                        ToolTip.delay: 1000;
                        ToolTip.timeout: 5000;
                        ToolTip.visible: hovered;
                        ToolTip.text: "Close the application.";

                        icon.source: "qrc:/other/application-exit.png";
                        icon.height: height - 18 * Config.scale;
                        icon.width: width - 18 * Config.scale;
                        icon.color: enabled ? "black" : "lightgrey";

                        onReleased: Qt.quit();
                    }
                }
            } //exit row

            Rectangle { // separator
                width: settingsPage.width;
                height: Math.max(1, Math.floor(1 * Config.scale));
                color: "lightgrey";
            }

        } // Column
    }
}
