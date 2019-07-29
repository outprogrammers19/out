import QtQuick 2.9
import QtQuick.Layouts 1.9
import QtQuick.Controls 2.9


Item {
    id: websitesPage;

    property bool needToReload: false;

    function reload() {
        loader.sourceComponent = null;
        loader.sourceComponent = mainComponent;
    }

    Connections {
        target: manager;
        onIsUpdatingChanged: {
            if (isUpdating === false)
                needToReload = true;
        }
        onRescaledChanged: {
            if (rescaled === true) {
                needToReload = true;
                manager.rescaled = false;
            }
        }
    }

    Rectangle {
        anchors.fill: parent;
        color: "white";
    }

    Loader {
        id: loader;
        anchors.fill: parent;
        sourceComponent: mainComponent;
    }

    Component {
        id: mainComponent;

        Flickable {
            property bool isScrollbarVisible: gridLayout.height > websitesPage.height;

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
                    model: websModel.count;
                    WebsiteTile { }
                }

                onHeightChanged: {
                    width: height > parent.height ? websitesPage.width - scrollBar.width : websitesPage.width;
                }
            }
        } // Flickable
    } // Component
}
