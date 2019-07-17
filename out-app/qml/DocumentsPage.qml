import QtQuick 2.9
import QtQuick.Layouts 1.9
import QtQuick.Controls 2.9


Item {
    id: documentsPage;

    property real buttonIconSize: Config.docEntryButtonHeight - 22 * Config.scale;
    property bool isScrollbarVisible: totalEntriesHeight > documentsPage.height;
    property int selectedIndex: -1;

    // auto-caculate height of all docs entries:
    property real totalEntriesHeight;

    function updateTotalEntiresHeight() {
        totalEntriesHeight = Config.docEntryHeight * docsModel.rowCount();
    }

    Component.onCompleted: updateTotalEntiresHeight();

    // ----- page structure -----

    Connections {
        target: docsModel;
        onRowsInserted: updateTotalEntiresHeight();
    }

    Rectangle {
        anchors.fill: parent;
        color: "white";
    }

    // structure of single document entry:
    Component {
        id: documentDelegate

        Item {
            width: documentsPage.width;
            height: Config.docEntryHeight;

            Rectangle {
                id: bg;
                anchors.fill: parent;
                anchors.topMargin: Math.max(1, Math.floor(1 * Config.scale));
                anchors.leftMargin: 20 * Config.scale;
                anchors.rightMargin: 20 * Config.scale;
                color: index === selectedIndex ? "#dddddd" : "transparent";
                //color: index === selectedIndex ? "lightgrey" : "transparent";

                MouseArea{
                    id: mouseArea;
                    anchors.fill: parent
                    onReleased: {
                        //if (index === selectedIndex)
                        //    selectedIndex = -1;
                        //else
                        selectedIndex = index;
                    }
                }
            }
            Label {
                id: docNameLabel;
                text: name;
                wrapMode: Label.WrapAnywhere;
                maximumLineCount: 1;
                anchors.verticalCenter: parent.verticalCenter;
                anchors.leftMargin: 35 * Config.scale;
                anchors.left: parent.left;
                anchors.right: openButton.left;
                font.pixelSize: Config.bigFontSize;
                font.bold: true;
            }
            Label {
                id: dateLabel;
                text: timestamp;
                font.pixelSize: Config.smallFontSize;
                anchors.bottom: parent.bottom;
                anchors.right: openButton.left;
                anchors.rightMargin: 10 * Config.scale;
            }
            Button {
                id: openButton;
                text: "Open";
                width: 140 * Config.scale;
                height: Config.docEntryButtonHeight;
                anchors.rightMargin: 40 * Config.scale;
                anchors.right: parent.right;
                anchors.verticalCenter: parent.verticalCenter;
                icon.source: "qrc:/other/app-icons/text-x-generic.png";
                icon.height: buttonIconSize;
                icon.width: buttonIconSize;
                icon.color: openButton.enabled ? "black" : "lightgrey";
                font.pixelSize: Config.bigFontSize;
                //font.bold: true;

                onReleased: console.log(url);
            }
            // top and bottom lines of entry:
            Rectangle {
                id: topLine;
                anchors.top: parent.top;
                anchors.left: parent.left;
                anchors.right: parent.right;
                anchors.leftMargin: 20 * Config.scale;
                anchors.rightMargin: 20 * Config.scale;
                height: index !== 0 ? 0 : Math.max(1, Math.floor(1 * Config.scale));
                color: "lightgrey";
            }
            Rectangle {
                id: bottomLine;
                anchors.top: parent.bottom;
                anchors.left: parent.left;
                anchors.right: parent.right;
                anchors.leftMargin: 20 * Config.scale;
                anchors.rightMargin: 20 * Config.scale;
                height: Math.max(1, Math.floor(1 * Config.scale));
                color: "lightgrey";
            }
        }
    } // Component documentDelegate

    ListView {
        id: listView;
        anchors.fill: parent
        clip: true
        model: docsModel
        delegate: documentDelegate
        interactive: isScrollbarVisible;

        ScrollBar.vertical: ScrollBar {
            id: scrollBar;
            width: Config.scrollbarWidth;
            policy: isScrollbarVisible ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff;
        }
    } // listView

    Button {
        onReleased: docsModel.tmp_initialize();
        anchors.bottom: parent.bottom;
    }
}
