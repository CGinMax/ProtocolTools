import QtQuick 2.12
import QtQuick.Controls 2.12

import Qaterial 1.0 as Qaterial

Rectangle {
    id: _root
    property int maxWidth: 1000
    property bool hovered: false
    property alias text: _content.text
    visible: _content.text.length != 0
    color: "#EFEFEF"
    radius: height / 2

    width: _content.contentWidth /*> maxWidth ? maxWidth : _content.contentWidth*/ + 10
    height: _content.contentHeight + 10

    Qaterial.Label {
        id: _content
        wrapMode: Text.WordWrap
        anchors.fill: parent
        anchors.margins: 5
    }
    MouseArea {
        id: mouse_area
        anchors.fill: parent
        hoverEnabled: true
        onEntered: _root.hovered = true
        onExited: _root.hovered = false
    }
}
