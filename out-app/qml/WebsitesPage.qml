/**
 * @file WebsitesPage.qml
 * @author Jakub Precht
 * @date 2019-08-01
 */

import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12


/**
 * @brief QML element that displays websites links as rectangular tiles with icons
 * and arranges them automatically in rows and columns.
 */
Item {
    id: websitesPage;

    /**
     * @brief True if the size or structure of this Item has changed.
     */
    property bool needToReload: false;

    // -------------------- FUNCTIONS --------------------

    /**
     * @brief Reload page layout
     */
    function reload() {
        loader.sourceComponent = null;
        loader.sourceComponent = mainComponent;
        needToReload = false;
    }

    /**
     * @brief Handle manager's isUpdatingChanged and rescaledChanged signals.
     */
    Connections {
        id: managerHandler;
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

    // -------------------- STRUCTURE --------------------

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

        /**
         * @brief Wraps gridLayout to enable scrolling (if neccessarily)
         */
        Flickable {
            id: gridFlickable
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

            /**
             * @brief It arranges WebsiteTiles into rows and columns.
             * The number of tiles is defined by WebsitesModel's count property.
             * Then Repeater is used to create that number of tiles inside the grid.
             */
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
