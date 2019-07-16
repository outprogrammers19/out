import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

ApplicationWindow {
    id: window;
    width: 900;
    height: 680;
    minimumWidth: 500;
    minimumHeight: 320;
    visible: true;

    header: ToolBar {
        id: toolBar;
        height: LayoutSettings.toolbarHeight;

        TabBar {
            id: tabBar;
            width: parent.width;
            anchors.left: parent.left;
            anchors.bottom: parent.bottom;
            contentHeight: LayoutSettings.toolbarHeight - 4;
            currentIndex: swipeView.currentIndex

            TabButton {
                id: webTabButton
                text: "Websites";
                font.pixelSize: LayoutSettings.bigFontSize;
                icon.source: "qrc:/other/app-icons/applications-internet.png";
                icon.height: webTabButton.height - 16;
                icon.width: webTabButton.height - 16;
//                font.bold: true;
            }
            TabButton {
                id: docsTabButton;
                text: "Documents";
                font.pixelSize: LayoutSettings.bigFontSize;
                icon.source: "qrc:/other/app-icons/document-open.png";
                icon.height: docsTabButton.height - 12;
                icon.width: docsTabButton.height - 12;
//                font.bold: true;
            }
            TabButton {
                id: settingsTabButton;
                text: "Settings";
                font.pixelSize: LayoutSettings.bigFontSize;
                icon.source: "qrc:/other/app-icons/system-run.png";
                icon.height: settingsTabButton.height - 16;
                icon.width: settingsTabButton.height - 16;
//                font.bold: true;
            }
        } // TabBar

//        Button {
//            id: updateButton;
//            anchors.verticalCenter: parent.verticalCenter;
//            height: LayoutSettings.buttonHeight;
//            anchors.right: exitButton.left;
//            anchors.rightMargin: 10;
//            font.pixelSize: LayoutSettings.bigFontSize;
//            text: "Update";
//            onReleased:; // TODO busy indicator + logic
//            visible: false;
//        }
//        Button {
//            id: exitButton;
//            anchors.verticalCenter: parent.verticalCenter;
//            height: LayoutSettings.buttonHeight;
//            anchors.right: parent.right;
//            font.pixelSize: LayoutSettings.bigFontSize;
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
        interactive: LayoutSettings.interactiveSwipe;

        WebsitesPage { }
        DocumentsPage { }
        SettingsPage { }
    }

    footer: ToolBar {
        width: parent.width;
        Label {
            id: statusLabel;
            leftPadding: 10;
            font.pixelSize: LayoutSettings.smallFontSize;
            anchors.verticalCenter: parent.verticalCenter;
            text: dataModel.status;
        }
    }

}
