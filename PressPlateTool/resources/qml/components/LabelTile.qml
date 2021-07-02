import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {
    id: _root
    property alias title: label_title.text
    property alias text: label_content.text

    property color titleColor: "gray"

    implicitWidth: Math.max(label_title.contentWidth, label_content.contentWidth)
    implicitHeight: label_title.contentHeight + label_content.contentHeight

    ColumnLayout {
        Label {
            id: label_title
            Layout.preferredWidth: contentWidth
            Layout.fillWidth: true
            Layout.fillHeight: true

            color: titleColor
            font.pixelSize: 5
        }
        Label {
            id: label_content
            Layout.preferredWidth: contentWidth
            Layout.fillWidth: true
            Layout.fillHeight: true

            font.pixelSize: 18
        }
    }
}
