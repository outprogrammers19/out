import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    width: LayoutSettings.tileWidth;
    height: LayoutSettings.tileHeight;

    Item {
        width: parent.width - 10;
        height: parent.height - 10;
        anchors.centerIn: parent;

        Button {
            id: webButton;
            focus: true;
            hoverEnabled: true;
            anchors.fill: parent;
            
            ToolTip.delay: 1000;
            ToolTip.timeout: 5000;
            ToolTip.visible: hovered;
            ToolTip.text: dataModel.name(index);
            
            onReleased: dataModel.openUrl(index);
            onHighlightedChanged: {
                console.log(highlighted)
            }

            onHoveredChanged: {
                var status = webButton.hovered ? dataModel.url(index) : "";
                dataModel.setStatus(status);
            }

            text: dataModel.icon(index) === "" ? dataModel.name(index) : "";
            font.pixelSize: LayoutSettings.smallFontSize;

            Image {
                id: webIcon;
                anchors.centerIn: parent;
                height: 0.9 * parent.height;
                width: 0.9 * parent.width;
                fillMode: Image.PreserveAspectFit;
                source: dataModel.icon(index);
            }
        } // webButton
    }
}
