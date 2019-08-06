/**
 * @file WebsiteTile.qml
 * @author Jakub Precht
 * @date 2019-08-01
 */

import QtQuick 2.0
import QtQuick.Controls 2.12

/**
 * @brief Defines button that once clicked, it opens corresponding link in the default browser
 */
Item {
    id: websiteTile;
    width: Config.tileWidth;
    height: Config.tileHeight;

    Item {
        width: parent.width - 10 * manager.guiScaleFactor;
        height: parent.height - 10 * manager.guiScaleFactor;
        anchors.centerIn: parent;

        Button {
            id: webButton;
            focus: true;
            hoverEnabled: true;
            anchors.fill: parent;
            
            ToolTip.delay: 1000;
            ToolTip.timeout: 5000;
            ToolTip.visible: hovered;
            ToolTip.text: "Open website: " + websModel.name(index);
            
            onReleased: manager.openUrl(websModel.url(index));

            onHoveredChanged: {
                var status = webButton.hovered ? websModel.url(index) : "";
                manager.setStatusMsg(status);
            }

            text: websModel.icon(index) === "" ? websModel.name(index) : "";
            font.pixelSize: Config.bigFontSize;

            // I couldn't find the option to properly scale button.icon,
            // so I decided load icon using Image as button's child
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
