import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Qaterial 1.0 as Qaterial

Qaterial.ModalDialog {
    id: _root

    property alias beginNum: _inputBegin.text
    property alias count: _inputCount.text

    title: qsTr("Sensor Number Configuration")

    contentItem: ColumnLayout
    {
        Qaterial.TextField {
            id: _inputBegin
            focus: true
            title: qsTr("Sensor Begin Number")
            text: "1"
            validator: IntValidator{ bottom: 1 }

            Layout.fillWidth: true
        }

        Qaterial.TextField {
            id: _inputCount
            title: qsTr("Sensor Count")
            text: "1"
            validator: IntValidator{ bottom: 1 }
            Layout.fillWidth: true
        }
    }
    footer: RowLayout {
        Qaterial.RawMaterialButton {
            Layout.alignment: Qt.AlignCenter
            text: qsTr("Confirm")
            onClicked: accept()
        }
        Qaterial.FlatButton {
            Layout.alignment: Qt.AlignCenter
            text: qsTr("Cancel")
            onClicked: reject()
        }
    }
}
