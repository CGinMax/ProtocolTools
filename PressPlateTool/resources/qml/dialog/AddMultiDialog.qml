import QtQuick 2.12
import QtQuick.Controls 2.12

import Qaterial 1.0 as Qaterial

Qaterial.ModalDialog {
    id: _root

    property alias beginNum: _inputBegin.text
    property alias count: _inputCount.text

    title: qsTr("Sensor Number Configuration")
    standardButtons: Dialog.Ok | Dialog.Cancel

    contentItem: Column
    {
        Qaterial.TextField {
            id: _inputBegin
            focus: true
            title: qsTr("Sensor Begin Number")
            text: "1"
            validator: IntValidator{ bottom: 1 }
        }

        Qaterial.TextField {
            id: _inputCount
            title: qsTr("Sensor Count")
            text: "1"
            validator: IntValidator{ bottom: 1 }
        }
    }
}
