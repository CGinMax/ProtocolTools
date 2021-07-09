import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Rectangle {
    id: _root

    property string text: ""
    property int value: 0xFF
    property color foreColor: "#9E9E9E"
    property color bgColor: "#F6F6F6"
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
            bgColor = "#FFBEC0";
            foreColor = "#E84B55";
        } else if (value === 1) {
            // green
            bgColor = "#ACF5D2";
            foreColor = "#1AB073";
        } else if (value === 0xFF) {
            // gray
            bgColor = "#F6F6F6";
            foreColor = "#9E9E9E";
        } else {
            // yellow
            bgColor = "#EFD360";
            foreColor = "#FFF6D7";
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
