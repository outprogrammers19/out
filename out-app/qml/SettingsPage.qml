import QtQuick 2.9

import QtQuick.Controls 2.9

Item {

    Rectangle {
        anchors.fill: parent;
        color: "white";
    }

    Column {
//        anchors.fill: parent;
        anchors.centerIn: parent;

        Item {
            width: 160;
            height: 160;
//            anchors.centerIn: parent;

            BusyIndicator { anchors.fill: parent; }

            // There is some bug in BusyIndicator, so let's leave it always on and use a cover to show it
            Rectangle {
                id: indicatoCover;
                anchors.fill: parent;
                color: manager.isUpdating ? "transparent" : "white";
            }
        }

        Button {
            width: 160;
            height: 60;
            text: "Update";
            font.pixelSize: Config.bigFontSize;
            onReleased: manager.update();
            enabled: !manager.isUpdating;
        }
    }

}
