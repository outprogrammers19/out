import QtQuick 2.0
import QtQuick.Controls 2.9

Item {
    id: websiteTile;

    width: Config.tileWidth;
    height: Config.tileHeight;

    Item {
        width: parent.width - 10 * Config.scale;
        height: parent.height - 10 * Config.scale;
        anchors.centerIn: parent;

        Button {
            id: webButton;
            focus: true;
            hoverEnabled: true;
            anchors.fill: parent;
            
            ToolTip.delay: 1000;
            ToolTip.timeout: 5000;
            ToolTip.visible: hovered;
            ToolTip.text: websModel.name(index);
            
            onReleased: websModel.openUrl(index);
            onHighlightedChanged: {
                console.log(highlighted)
            }

            onHoveredChanged: {
                var status = webButton.hovered ? websModel.url(index) : "";
                websModel.setStatus(status);
            }

            text: websModel.icon(index) === "" ? websModel.name(index) : "";
            font.pixelSize: Config.bigFontSize;

            Image {
                id: webIcon;
                anchors.centerIn: parent;
                height: 0.9 * parent.height;
                width: 0.9 * parent.width;
                fillMode: Image.PreserveAspectFit;
                source: websModel.icon(index);
            }
        } // webButton
    }
}
