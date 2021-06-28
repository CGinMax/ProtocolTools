import QtQuick 2.12
import QtQuick.Controls 2.12
import Qaterial 1.0 as Qaterial

Rectangle {
    id: _root

    Qaterial.Frame {
        id: _frame_serialport
        SerialPortConfigureView {
            id: _view_serialport
            isMultiConf: false
            isInWindow: false
            anchors.fill: parent
    //        width: 400
    //        height: 300
        } // SerialPortConfigureView
    }


    Qaterial.Button {
        id: _btn_save
        text: qsTr("Save")

        anchors.right: _root.right
        anchors.top: _frame_serialport.bottom
        anchors.rightMargin: 5
        anchors.topMargin: 5

        onPressed: {

        }
    }
}
