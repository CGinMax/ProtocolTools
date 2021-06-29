import QtQuick 2.12
import QtQuick.Controls 2.12

import Qaterial 1.0 as Qaterial

Rectangle {
    id: _root
    property alias text: _content.text

    color: "#EFEFEF"
    radius: height / 2

    width: _content.contentWidth + 10
    height: _content.contentHeight + 10

    Qaterial.Label {
        id: _content
        maximumLineCount: 30
        anchors.fill: parent
//        anchors.topMargin: 5
//        anchors.leftMargin: 5
        anchors.margins: 5
    }
}
