import QtQuick 2.12
import QtQuick.Controls 2.12
import Qaterial 1.0 as Qaterial

Rectangle {
    id: _root

    Qaterial.GroupBox {
        id: box_serialport
        title: qsTr("Serial Port Configuration")
        inlineTitle: true
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
        SerialPortConfigureView {
            id: _view_serialport
            isMultiConf: false
            isInWindow: false
            anchors.fill: parent
        } // SerialPortConfigureView
    }

    Qaterial.GroupBox {
        id: box_timeout
        title: qsTr("Gather Timeout Configuration")
        inlineTitle: true
        anchors.left: box_serialport.right
        anchors.leftMargin: 5
        anchors.top: box_serialport.top
        anchors.topMargin: 10
        Column {
            Qaterial.TextField {
                title: qsTr("Gather Timeout Time")
            }
            Qaterial.TextField {
                title: qsTr("Sensor Timeout Time")
            }
        }
    }


    Qaterial.FlatButton {
        id: btn_save
        text: qsTr("Save")

        anchors.right: _root.right
        anchors.top: box_serialport.bottom
        anchors.rightMargin: 5
        anchors.topMargin: 5

        onPressed: {

        }
    }
}
