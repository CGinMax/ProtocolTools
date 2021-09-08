import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "../data"

Rectangle {
    id: _root
    property string prefixText: ""
    property string suffixText: ""
    property alias textColor: _text.color
    property alias bgColor: _root.color

    implicitWidth: _text.width + 10
    implicitHeight: _text.height + 10

    color: ThemeConfig.unknowBgColor
    radius: 5
    ColumnLayout {
        anchors.fill: parent
        Label {
            Layout.alignment: Qt.AlignCenter
            id: _text
            text: _root.prefixText + _root.suffixText
            color: ThemeConfig.unknowFgColor
            font.pixelSize: 36
        }

    }
}
