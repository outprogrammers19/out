import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ApplicationWindow {
    id: window;
    width: 800;
    height: 600;
    visible: true;

    SystemPalette {
        id: palette;
    }

    header: ToolBar {
        id: toolBar;
        height: exitButton.height + 6;
        Button {
            id: exitButton;
            anchors.verticalCenter: parent.verticalCenter;
            text: "Exit";
            onReleased: Qt.quit();
            anchors.right: parent.right;
            Component.onCompleted: {
                if (height < LayoutSettings.minimumToolbarButtonHeight)
                    height = LayoutSettings.minimumToolbarButtonHeight;
            }
        }
    }

    TilesGrid {
        anchors.centerIn: parent;
        width: parent.width;
        height: parent.height;
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
