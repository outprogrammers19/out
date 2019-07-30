/**
 * @file MainWindow.qml
 * @author Jakub Precht
 * @date 2019-08-01
 */

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

/**
 * @brief The main window of QML GUI, loaded in main.cpp.
 */
ApplicationWindow {
    id: window;
    visible: true;

    width: 900 * Config.scale;
    height: 680 * Config.scale;
    minimumWidth: 500 * Config.scale;
    minimumHeight: 320 * Config.scale;

    /**
     * @brief TabBar used to switch between 3 tabs: website, documents and settings.
     */
    header: ToolBar {
        id: toolBar;
        height: Config.toolbarHeight;

        TabBar {
            id: tabBar;
            width: parent.width;
            anchors.left: parent.left;
            anchors.bottom: parent.bottom;
            contentHeight: Config.toolbarHeight - 4 * Config.scale;
            currentIndex: swipeView.currentIndex

            TabButton {
                id: webTabButton
                text: "Websites";
                font.pixelSize: Config.bigFontSize;
                icon.source: "qrc:/other/applications-internet.png";
                icon.height: webTabButton.height - 19 * Config.scale;
                icon.width: webTabButton.height - 19 * Config.scale;
                //font.bold: true;
            }
            TabButton {
                id: docsTabButton;
                text: "Documents";
                font.pixelSize: Config.bigFontSize;
                icon.source: "qrc:/other/document-open.png";
                icon.height: docsTabButton.height - 14 * Config.scale;
                icon.width: docsTabButton.height - 14 * Config.scale;
                //font.bold: true;
            }
            TabButton {
                id: settingsTabButton;
                text: "Settings";
                font.pixelSize: Config.bigFontSize;
                icon.source: "qrc:/other/system-run.png";
                icon.height: settingsTabButton.height - 19 * Config.scale;
                icon.width: settingsTabButton.height - 19 * Config.scale;
                //font.bold: true;
            }
        } // TabBar
    } // ToolBar

    /**
     * @brief SwipeView is responsible for drawing and updating pages depending on currently chosen tab in TabBar
     */
    SwipeView {
        id: swipeView
        anchors.centerIn: parent;
        width: parent.width;
        height: parent.height;
        currentIndex: tabBar.currentIndex
        interactive: Config.interactiveSwipe;
        enabled: !manager.isUpdating;

        WebsitesPage { id: websitesPage; }
        DocumentsPage { }
        SettingsPage { }

        onCurrentIndexChanged: {
            if (currentIndex === 0 && websitesPage.needToReload === true)
                websitesPage.reload();
        }
    }

    /**
     * @brief Footer's job is to display additional information depending on what is currently hovered by the mouse cursor.
     */
    footer: ToolBar {
        id: footer;
        width: parent.width;
        height: 26 * Config.scale;

        Label {
            id: statusLabel;
            leftPadding: 10 * Config.scale;
            font.pixelSize: Config.normalFontSize;
            anchors.verticalCenter: parent.verticalCenter;
            text: manager.statusMsg;
        }
    }

}
