import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12


Item {
    id: documentsPage;

    property int buttonIconSize: LayoutSettings.buttonHeight - 14;
    property int totalEntriesHeight: LayoutSettings.documentEntryHeight * listModel.count;
    property bool isScrollbarVisible: totalEntriesHeight > documentsPage.height;
    property int selectedIndex: -1;

    Rectangle {
        anchors.fill: parent;
        color: "white";
    }

    ListModel {
        id: listModel
        ListElement {
            name: "Prospectus";
            date: "2019-07-15";
        }
        ListElement {
            name: "Almanac";
            date: "2019-07-15";
        }
        ListElement {
            name: "Examination information";
            date: "2019-07-15";
        }
        ListElement {
            name: "Prospectus";
            date: "2019-07-15";
        }
        ListElement {
            name: "Almanac";
            date: "2019-07-15";
        }
        ListElement {
            name: "Examination information";
            date: "2019-07-15";
        }
    } // ListModel

    Component {
        id: documentDelegate

        Item {
            width: documentsPage.width;
            height: LayoutSettings.documentEntryHeight;

            Rectangle {
                id: bg;
                anchors.fill: parent;
                anchors.topMargin: 1;
                anchors.leftMargin: 20;
                anchors.rightMargin: 20;
                color: index === selectedIndex ? "#dddddd" : "transparent";
                // color: index === selectedIndex ? "lightgrey" : "transparent";

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
                anchors.verticalCenter: parent.verticalCenter;
                anchors.leftMargin: 30;
                anchors.left: parent.left;
                anchors.right: dateLabel.left;
                font.pixelSize: LayoutSettings.bigFontSize;
                font.bold: true;
            }
            Label {
                id: dateLabel;
                text: date;
                anchors.bottom: parent.bottom;
                anchors.right: fileButton.left;
                anchors.rightMargin: 10;
            }
            Button {
                id: fileButton;
                text: "File";
                width: 100;
                height: LayoutSettings.buttonHeight;
                anchors.rightMargin: 20;
                anchors.right: linkButton.left;
                anchors.verticalCenter: parent.verticalCenter;
                font.pixelSize: LayoutSettings.bigFontSize;
                icon.source: "qrc:/other/app-icons/text-x-generic.png";
                icon.height: buttonIconSize;
                icon.width: buttonIconSize;
                icon.color: fileButton.enabled ? "black" : "lightgrey";
                //                font.bold: true;
                //                enabled: false;
            }
            Button {
                id: linkButton;
                text: "Link";
                width: 100;
                height: LayoutSettings.buttonHeight;
                anchors.rightMargin: 35;
                anchors.right: parent.right;
                anchors.verticalCenter: parent.verticalCenter;
                // icon.source: "qrc:/other/app-icons/text-html.png";
                icon.source: "qrc:/other/app-icons/applications-internet.png";
                icon.height: buttonIconSize;
                icon.width: buttonIconSize;
                icon.color: linkButton.enabled ? "black" : "lightgrey";
                font.pixelSize: LayoutSettings.bigFontSize;
                //                font.bold: true;
            }
            Rectangle {
                id: topLine;
                anchors.top: parent.top;
                anchors.left: parent.left;
                anchors.right: parent.right;
                anchors.leftMargin: 20;
                anchors.rightMargin: 20;
                height: index === 0 ? 1 : 0;
                color: "lightgrey";
            }
            Rectangle {
                id: bottomLine;
                anchors.top: parent.bottom;
                anchors.left: parent.left;
                anchors.right: parent.right;
                anchors.leftMargin: 20;
                anchors.rightMargin: 20;
                height: 1;
                color: "lightgrey";
            }
        }
    } // Component documentDelegate

    ListView {
        id: listView;
        anchors.fill: parent
        clip: true
        model: listModel
        delegate: documentDelegate
        interactive: isScrollbarVisible;

        ScrollBar.vertical: ScrollBar {
            id: scrollBar;
            width: LayoutSettings.scrollbarWidth;
            policy: isScrollbarVisible ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff;
        }
    } // listView

}
