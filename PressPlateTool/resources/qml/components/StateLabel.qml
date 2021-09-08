import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import "../data"

Rectangle {
    id: _root

    property string text: ""
    property int value: 0xFF
    property color foreColor: ThemeConfig.unknowFgColor
    property color bgColor: ThemeConfig.unknowBgColor
    property bool hovered: false
    color: bgColor
    radius: 4

    implicitWidth: 110
    RowLayout {
        anchors.fill: parent
        Rectangle {
            Layout.preferredWidth: 6
            Layout.preferredHeight: 6
            Layout.leftMargin: 5
            radius: 3
            color: _root.foreColor
        }
        Text {
            text: _root.text
            color: _root.foreColor
            font.pixelSize: 14
            width: contentWidth
            Layout.alignment: Qt.AlignVCenter
        }
    }
    onValueChanged: {
        if (value === 0) {
            // red
            bgColor = ThemeConfig.openBgColor;
            foreColor = ThemeConfig.openFgColor;
        } else if (value === 1) {
            // green
            bgColor = ThemeConfig.closeBgColor;
            foreColor = ThemeConfig.closeFgColor;
        } else if (value === 0xFF) {
            // gray
            bgColor = ThemeConfig.unknowBgColor;
            foreColor = ThemeConfig.unknowFgColor;
        } else {
            // yellow
            bgColor = ThemeConfig.exceptionBgColor;
            foreColor = ThemeConfig.exceptionFgColor;
        }
    }

    MouseArea {
        id: mouse_area
        anchors.fill: parent
        hoverEnabled: true
        onEntered: _root.hovered = true
        onExited: _root.hovered = false
    }
}
