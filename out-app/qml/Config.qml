pragma Singleton
import QtQuick 2.12

// TODO Config as .init file read and provided by c++ model

QtObject {
    // NOTE: describe scaling mechanizam
    property real scale : 1.0;

    property real tileHeight: 120 * scale;
    property real tileWidth: 220  * scale;
    property real toolbarHeight: 52 * scale;
    property real buttonHeight: 40 * scale;
    property real documentEntryHeight: 54 * scale;
    property real toolbarHorizonatalSpaceSize: 1 * scale;
    property real scrollbarWidth: 16 * scale;
    property real bigFontSize: 18 * scale;
    property real normalFontSize: 15 * scale;
    property real smallFontSize: 13 * scale;

    property bool interactiveSwipe: false;
}
