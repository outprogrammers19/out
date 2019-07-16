import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12


Item {
    id: websitesPage;

    property bool isScrollbarVisible: gridLayout.height > websitesPage.height;

    Rectangle {
        anchors.fill: parent;
        color: "white";
    }

    Flickable {
        width: parent.width;
        height: parent.height - 2 * Config.toolbarHorizonatalSpaceSize; // NOTE: no need to multiply by scale
        anchors.centerIn: parent;
        contentHeight: gridLayout.height
        contentWidth: gridLayout.width
        flickableDirection: Flickable.AutoFlickIfNeeded;
        // interactive: false;

        ScrollBar.vertical: ScrollBar {
            id: scrollBar;
            width: Config.scrollbarWidth;
            policy: isScrollbarVisible ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff;
        }

        GridLayout {
            id: gridLayout;
            width: websitesPage.width - scrollBar.width;
            anchors.centerIn: parent;
            columns: Math.max(1, width / Config.tileWidth);
            columnSpacing: 0;
            rowSpacing: 0;

            Repeater {
                model: dataModel.count();
                WebsiteTile { }
            }

            onHeightChanged: {
                width: height > parent.height ? websitesPage.width - scrollBar.width : websitesPage.width;
            }
        }
    } // Flickable

//    Rectangle {
//        width: parent.width;
//        height: Config.toolbarHorizonatalSpaceSize;
//        color: "white";
//        anchors.top: parent.top;
//    }

//    Rectangle {
//        width: parent.width;
//        height: Config.toolbarHorizonatalSpaceSize;
//        color: "white";
//        anchors.bottom: parent.bottom;
//    }
}
