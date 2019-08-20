/**
 * @file SettingsPage.qml
 * @author Jakub Precht
 * @date 2019-08-01
 */

import QtQuick 2.12
import QtQuick.Controls 2.12

/**
 * @brief Defines means to update, scale and exit the application.
 */
Item {
    id: settingsPage;

    /**
     * @brief Handle manager updateFinished signal
     */
    Connections {
        id: managerHandler;
        target: manager;
        onUpdateFinished: {
            if (status === true)
                successStatus.visible = true;
            else
                failedStatus.visible = true;
        }
    }

    // -------------------- STRUCTURE --------------------

    Rectangle {
        anchors.fill: parent;
        color: "white";
    }

    /**
     * @brief Wrap settings with ScrollBar (if necessarily)
     */
    Flickable {
        id: settingsFlickable;
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

        /**
         * @brief Column where each entry defines a different row with different option
         */
        Column {
            id: settingsColumn;
            anchors.fill: parent;
            width: settingsPage.width;
            property real contentHeight: 4 * Math.max(1, Math.floor(1 * manager.guiScaleFactor))
                                         + updatesRow.height
                                         + settingsRow.height
                                         + exitRow.height
                                         + serverRow.height;

            Rectangle { // separator
                width: settingsPage.width;
                height: Math.max(1, Math.floor(1 * manager.guiScaleFactor));
                color: "lightgrey";
            }

            /**
             * @brief Updaes row has a success/fail label next to the title that shows the status of last update attempt.
             * It also has a busy indicator that appears when update is in process.
             */
            Rectangle { // Updates row
                id: updatesRow;
                width: settingsPage.width;
                height: 100 * manager.guiScaleFactor;

                Label {
                    id: updateLabel
                    text: "Updates:";
                    font.pixelSize: Config.bigFontSize;
                    font.bold: true;
                    x: 20 * manager.guiScaleFactor;
                    y: 20 * manager.guiScaleFactor;
                }

                Label {
                    font.pixelSize: Config.bigFontSize;
                    id: successStatus;
                    text: "Up-to-date";
                    color: "green";
                    anchors.left: updateLabel.right;
                    anchors.leftMargin: 6 * manager.guiScaleFactor;
                    y: 20 * manager.guiScaleFactor;
                    visible: false;
                }
                Label {
                    font.pixelSize: Config.bigFontSize;
                    id: failedStatus;
                    text: "Failed";
                    color: "red";
                    anchors.left: updateLabel.right;
                    anchors.leftMargin: 6 * manager.guiScaleFactor;
                    y: 20 * manager.guiScaleFactor;
                    visible: false;
                }

                Item {
                    height: parent.height;
                    anchors.centerIn: parent;
                    width: 400 * manager.guiScaleFactor;

                    Item {
                        id: busyIndicator;
                        width: 65 * manager.guiScaleFactor;
                        height: 65 * manager.guiScaleFactor;
                        anchors.verticalCenter: parent.verticalCenter;
                        anchors.right: updateButton.left;
                        anchors.rightMargin: 10 * manager.guiScaleFactor;

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
                        width: 140 * manager.guiScaleFactor;
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
                        icon.height: Config.docEntryButtonHeight - 22 * manager.guiScaleFactor;
                        icon.width: Config.docEntryButtonHeight - 22 * manager.guiScaleFactor;
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
                height: Math.max(1, Math.floor(1 * manager.guiScaleFactor));
                color: "lightgrey";
            }

            /**
             * @brief This row allows to change server URL address used for updates. In case of accidental changes there is a reset button
             * to restore default value.
             */
            Rectangle { // Server URL row
                id: serverRow;
                width: settingsPage.width;
                height: 140 * manager.guiScaleFactor;

                Label {
                    id: serverLabel
                    text: "Server URL:";
                    font.pixelSize: Config.bigFontSize;
                    font.bold: true;
                    x: 20 * manager.guiScaleFactor;
                    y: 20 * manager.guiScaleFactor;
                }


                Item {
                    height: parent.height;
                    anchors.centerIn: parent;
                    width: 400 * manager.guiScaleFactor;

                    TextField {
                        id: serverTextField;
                        font.pixelSize: Config.normalFontSize;
                        x: -40 * manager.guiScaleFactor;
                        y: 52 * manager.guiScaleFactor;
                        width: 290 * manager.guiScaleFactor;
                        height: 36 * manager.guiScaleFactor;
                        text: manager.serverUrl;
                    }

                    Button {
                        id: defaultServerButton;
                        width: 140 * manager.guiScaleFactor;
                        height: Config.docEntryButtonHeight;
                        y: 15 * manager.guiScaleFactor;
                        anchors.right: parent.right;
                        text: "Default";
                        font.pixelSize: Config.bigFontSize;

                        hoverEnabled: true;
                        ToolTip.delay: 1000;
                        ToolTip.timeout: 5000;
                        ToolTip.visible: hovered;
                        ToolTip.text: "Restore the default URL.";

                        icon.source: "qrc:/other/edit-undo.png";
                        icon.height: Config.docEntryButtonHeight - 18 * manager.guiScaleFactor;
                        icon.width: Config.docEntryButtonHeight - 18 * manager.guiScaleFactor;
                        icon.color: enabled ? "black" : "lightgrey";

                        onReleased: {
                            manager.resetServerUrl();
                        }
                    }

                    Button {
                        id: newServerButton;
                        width: 140 * manager.guiScaleFactor;
                        height: Config.docEntryButtonHeight;
                        y: 75 * manager.guiScaleFactor;
                        anchors.right: parent.right;
                        text: "Change";
                        font.pixelSize: Config.bigFontSize;
                        enabled: serverTextField.text != manager.serverUrl;

                        hoverEnabled: true;
                        ToolTip.delay: 1000;
                        ToolTip.timeout: 5000;
                        ToolTip.visible: hovered;
                        ToolTip.text: "Set new ULR value.";

                        icon.source: "qrc:/other/dialog-ok.png";
                        icon.height: Config.docEntryButtonHeight - 18 * manager.guiScaleFactor;
                        icon.width: Config.docEntryButtonHeight - 18 * manager.guiScaleFactor;
                        icon.color: enabled ? "black" : "lightgrey";

                        onReleased: {
                            manager.serverUrl = serverTextField.text;
                        }
                    }
                }
            } // !Server URL row

            Rectangle { // separator
                width: settingsPage.width;
                height: Math.max(1, Math.floor(1 * manager.guiScaleFactor));
                color: "lightgrey";
            }

            /**
             * @brief The row create a Slider that is used to select GUI scale factor.
             */
            Rectangle { // Scale row
                id: settingsRow;
                width: settingsPage.width;
                height: 100 * manager.guiScaleFactor;

                Label {
                    id: scaleLabel;
                    text: "Interface Scale Factor:";
                    font.pixelSize: Config.bigFontSize;
                    font.bold: true;
                    x: 20 * manager.guiScaleFactor;
                    y: 10 * manager.guiScaleFactor;
                }
                Label {
                    text: slider.value.toFixed(2);
                    font.pixelSize: Config.bigFontSize;
                    anchors.left: scaleLabel.right;
                    anchors.leftMargin: 6 * manager.guiScaleFactor;
                    y: 10 * manager.guiScaleFactor;
                }
                Item {
                    anchors.centerIn: parent;
                    width: scaleRow.width + scaleButton.width;
                    height: parent.height;

                    Item { // Scale row
                        id: scaleRow;
                        height: 100 * manager.guiScaleFactor;
                        width: slider.width * slider.scale;

                        Slider {
                            id: slider;
                            y: 48 * manager.guiScaleFactor;
                            width: 120; // NOTE: do not multiply by manager.guiScaleFactor, you multiplied slider.scale
                            anchors.horizontalCenter: parent.horizontalCenter;
                            from: 0.75;
                            value: manager.guiScaleFactor;
                            to: 2.0;
                            snapMode: Slider.SnapAlways;
                            stepSize: 0.125;
                            scale: 2.0 * manager.guiScaleFactor;
                        }
                    }
                    Button {
                        id: scaleButton;
                        width: 140 * manager.guiScaleFactor;
                        height: Config.docEntryButtonHeight;
                        text: "Apply";
                        font.pixelSize: Config.bigFontSize;
                        anchors.verticalCenter: scaleRow.verticalCenter;
                        anchors.left: scaleRow.right;
                        anchors.leftMargin: 10 * manager.guiScaleFactor;
                        enabled: slider.value !== manager.guiScaleFactor;

                        hoverEnabled: true;
                        ToolTip.delay: 1000;
                        ToolTip.timeout: 5000;
                        ToolTip.visible: hovered;
                        ToolTip.text: "Re-scale application with the new scale factor."

                        icon.source: "qrc:/other/view-fullscreen.png";
                        icon.height: Config.docEntryButtonHeight - 22 * manager.guiScaleFactor;
                        icon.width: Config.docEntryButtonHeight - 22 * manager.guiScaleFactor;
                        icon.color: enabled ? "black" : "lightgrey";

                        onReleased: {
                            manager.guiScaleFactor = slider.value;
                            manager.rescaled = true;
                        }
                    }
                }
            } // !Scale row

            Rectangle { // separator
                width: settingsPage.width;
                height: Math.max(1, Math.floor(1 * manager.guiScaleFactor));
                color: "lightgrey";
            }

            /**
             * @brief Exit row will terminate application in a normal way.
             */
            Rectangle { // Exit row
                id: exitRow;
                width: settingsPage.width;
                height: 100 * manager.guiScaleFactor;

                Item {
                    height: parent.height;
                    anchors.centerIn: parent;
                    width: 400 * manager.guiScaleFactor;


                    Button {
                        id: exitButton;
                        width: 140 * manager.guiScaleFactor;
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
                        icon.height: Config.docEntryButtonHeight - 18 * manager.guiScaleFactor;
                        icon.width: Config.docEntryButtonHeight - 18 * manager.guiScaleFactor;
                        icon.color: enabled ? "black" : "lightgrey";

                        onReleased: Qt.quit();
                    }
                }
            } //exit row

            Rectangle { // separator
                width: settingsPage.width;
                height: Math.max(1, Math.floor(1 * manager.guiScaleFactor));
                color: "lightgrey";
            }

        } // Column
    }
}
