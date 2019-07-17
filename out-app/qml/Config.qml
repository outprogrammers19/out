pragma Singleton
import QtQuick 2.9

// TODO Config as .init file read and provided by c++ model

QtObject {
    // NOTE: describe scaling mechanizam
    property real scale : 1.0;

    property real tileHeight: 120 * scale;
    property real tileWidth: 220  * scale;
    property real toolbarHeight: 52 * scale;
    property real docEntryButtonHeight: 48 * scale;
    property real docEntryHeight: 60 * scale;
    property real toolbarHorizonatalSpaceSize: 1 * scale;
    property real scrollbarWidth: 16 * scale;
    property real bigFontSize: 19 * scale;
    property real normalFontSize: 15 * scale;
    property real smallFontSize: 12 * scale;

    property bool interactiveSwipe: false; // TODO true for mobile, false for desktop
}
