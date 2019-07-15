import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.13

ApplicationWindow {
    id: window;
    width: 800;
    height: 600;
    visible: true;

    header: ToolBar {
        id: toolBar;
        height: exitButton.height + 16;

        TabBar {
            id: tabBar;
            width: 400;
            anchors.left: parent.left;
            anchors.bottom: parent.bottom;
            contentHeight: parent.height - 6;
            currentIndex: swipeView.currentIndex

            TabButton {
                text: "Websites";
                font.pixelSize: LayoutSettings.bigFontSize;
            }
            TabButton {
                text: "Documents";
                font.pixelSize: LayoutSettings.bigFontSize;
            }
        }

        Button {
            id: updateButton;
            anchors.verticalCenter: parent.verticalCenter;
            height: LayoutSettings.toolbarButtonHeight;
            anchors.right: exitButton.left;
            anchors.rightMargin: 10;
            font.pixelSize: LayoutSettings.bigFontSize;
            text: "Update";
            onReleased:; // TODO busy indicator + logic
        }

        Button {
            id: exitButton;
            anchors.verticalCenter: parent.verticalCenter;
            height: LayoutSettings.toolbarButtonHeight;
            anchors.right: parent.right;
            font.pixelSize: LayoutSettings.bigFontSize;
            text: "Exit";
            onReleased: Qt.quit();
        }
    }

    SwipeView {
        id: swipeView
        anchors.centerIn: parent;
        width: parent.width;
        height: parent.height;
        currentIndex: tabBar.currentIndex
//        interactive: false;

        WebsitesPage { }
        DocumentsPage { }
    }


    footer: ToolBar {
        width: parent.width;
        Label {
            id: statusLabel;
            leftPadding: 10;
            anchors.verticalCenter: parent.verticalCenter;
            text: dataModel.status;
        }
    }

}
