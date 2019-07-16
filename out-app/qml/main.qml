import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

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
                icon.source: "qrc:/other/app-icons/applications-internet.png";
                icon.height: webTabButton.height - 16 * Config.scale;
                icon.width: webTabButton.height - 16 * Config.scale;
//                font.bold: true;
            }
            TabButton {
                id: docsTabButton;
                text: "Documents";
                font.pixelSize: Config.bigFontSize;
                icon.source: "qrc:/other/app-icons/document-open.png";
                icon.height: docsTabButton.height - 12 * Config.scale;
                icon.width: docsTabButton.height - 12 * Config.scale;
//                font.bold: true;
            }
            TabButton {
                id: settingsTabButton;
                text: "Settings";
                font.pixelSize: Config.bigFontSize;
                icon.source: "qrc:/other/app-icons/system-run.png";
                icon.height: settingsTabButton.height - 16 * Config.scale;
                icon.width: settingsTabButton.height - 16 * Config.scale;
//                font.bold: true;
            }
        } // TabBar

//        Button {
//            id: updateButton;
//            anchors.verticalCenter: parent.verticalCenter;
//            height: Config.buttonHeight;
//            anchors.right: exitButton.left;
//            anchors.rightMargin: 10;
//            font.pixelSize: Config.bigFontSize;
//            text: "Update";
//            onReleased:; // TODO busy indicator + logic
//            visible: false;
//        }
//        Button {
//            id: exitButton;
//            anchors.verticalCenter: parent.verticalCenter;
//            height: Config.buttonHeight;
//            anchors.right: parent.right;
//            font.pixelSize: Config.bigFontSize;
//            text: "Exit";
//            onReleased: Qt.quit();
//        }
    } // ToolBar

    SwipeView {
        id: swipeView
        anchors.centerIn: parent;
        width: parent.width;
        height: parent.height;
        currentIndex: tabBar.currentIndex
        interactive: Config.interactiveSwipe;

        WebsitesPage { }
        DocumentsPage { }
        SettingsPage { }
    }

    footer: ToolBar {
        width: parent.width;
        Label {
            id: statusLabel;
            leftPadding: 10 * Config.scale;
            font.pixelSize: Config.normalFontSize;
            anchors.verticalCenter: parent.verticalCenter;
            text: dataModel.status;
        }
    }

}
