import QtQuick 2.12

import Qaterial 1.0 as Qaterial
Rectangle {

    width: 2
    color: "grey"
    Rectangle {
        width: 32
        height: 32
        radius: height / 2
        border.color: "grey"
        color: "white"
        anchors.top: parent.top
        anchors.topMargin: parent.height / 11
        anchors.horizontalCenter: parent.horizontalCenter
        Qaterial.RoundButton {
            icon.source: view_gather_config.isCollapse ? "image://faicon/angle-right" : "image://faicon/angle-left"
            icon.color: "grey"

            anchors.fill: parent
            onClicked: view_gather_config.collapse()
        }
    }
}
