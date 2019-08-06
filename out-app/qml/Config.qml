/**
 * @file Config.qml
 * @author Jakub Precht
 * @date 2019-08-01
 */

pragma Singleton
import QtQuick 2.12

/**
 * @brief GUI settings globally visible to all QML elements.
 */
QtObject {
    id: config;

    property real tileHeight: 120 * manager.guiScaleFactor;
    property real tileWidth: 220  * manager.guiScaleFactor;
    property real toolbarHeight: 52 * manager.guiScaleFactor;
    property real docEntryButtonHeight: 48 * manager.guiScaleFactor;
    property real docEntryHeight: 60 * manager.guiScaleFactor;
    property real toolbarHorizonatalSpaceSize: 1 * manager.guiScaleFactor;
    property real scrollbarWidth: 16 * manager.guiScaleFactor;
    property real bigFontSize: 19 * manager.guiScaleFactor;
    property real normalFontSize: 15 * manager.guiScaleFactor;
    property real smallFontSize: 12 * manager.guiScaleFactor;

    property bool interactiveSwipe: false; // TODO true for mobile, false for desktop
}
