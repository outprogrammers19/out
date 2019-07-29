import QtQuick 2.9
import QtQuick.Controls 2.9
import QtQuick.Layouts 1.9

ApplicationWindow {
    id: window;
    visible: true;

    width: 900 * Config.scale;
    height: 680 * Config.scale;
    minimumWidth: 500 * Config.scale;
    minimumHeight: 320 * Config.scale;

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
            if (currentIndex === 0 && websitesPage.needToReload === true) {
                websitesPage.reload();
                websitesPage.needToReload = false;
            }
        }
    }

    footer: ToolBar {
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
