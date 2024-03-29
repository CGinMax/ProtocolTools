import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls 1.4 as Old

import Qaterial 1.0 as Qaterial


Rectangle {
    id: _root
    property var gatherController: undefined

    ColumnLayout {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: parent.height / 2
        Layout.margins: 10
        spacing: 30
        TestState {
            Layout.fillWidth: true
//            Layout.fillHeight: true
            Layout.margins: 10
            Layout.alignment: Qt.AlignTop
            gatherController: _root.gatherController
        }

        TestAddress {
            gatherController: _root.gatherController

            Layout.fillWidth: true
//            Layout.fillHeight: true
            Layout.margins: 10
            Layout.alignment: Qt.AlignTop
        }
    }

}
