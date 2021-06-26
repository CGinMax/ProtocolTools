import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import Qaterial 1.0 as Qaterial

import "../page"

Rectangle {
    id: _root

    signal deleteAll()

    implicitWidth: 100
    implicitHeight: 50

    RowLayout {
        id: btn_tool_bar_layout

        property int _iconWidth: 18
        property int _iconHeight: 18

        spacing: 2
        anchors.fill: parent


        Qaterial.Button {
            id: btn_add_one
//            Layout.fillWidth: true
            Layout.alignment: Qt.AlignRight
            Layout.preferredWidth: parent._iconWidth * 2.5
            Layout.preferredHeight: parent._iconHeight * 2.5
            Layout.minimumWidth: parent._iconWidth
            Layout.minimumHeight: parent._iconHeight
            Layout.maximumWidth: 50
            icon.source: "qrc:/icons/add-one.png"
            icon.color: "black"
            icon.width: parent._iconWidth
            icon.height: parent._iconHeight
            flat: true
            backgroundColor: "transparent"

            onClicked: _dlg_serialport.showDialog(false)

        }
        Qaterial.Button {
            id: btn_add_multiple
//            Layout.fillWidth: true
            Layout.alignment: Qt.AlignRight
            Layout.preferredWidth: parent._iconWidth * 2.5
            Layout.preferredHeight: parent._iconHeight * 2.5
            Layout.minimumWidth: parent._iconWidth
            Layout.minimumHeight: parent._iconHeight
            Layout.maximumWidth: 50
            icon.source: "qrc:/icons/add-multi.png"
            icon.color: "black"
            icon.width: parent._iconWidth
            icon.height: parent._iconHeight
            flat: true
            backgroundColor: "transparent"

            onClicked: _dlg_serialport.showDialog(true)
        }

        Qaterial.Button{
            id: btn_delete_all
//            Layout.fillWidth: true
            Layout.alignment: Qt.AlignRight
            Layout.preferredWidth: parent._iconWidth * 2.5
            Layout.preferredHeight: parent._iconHeight * 2.5
            Layout.minimumWidth: parent._iconWidth
            Layout.minimumHeight: parent._iconHeight
            Layout.maximumWidth: 50
            icon.source: "qrc:/icons/delete-all.png"
            icon.color: "red"
            icon.width: parent._iconWidth
            icon.height: parent._iconHeight
            flat: true
            backgroundColor: "transparent"

            onClicked: {
                emit: _root.deleteAll()
            }
        }

    }


    // Window attach property can not use in child item
    function computeDialogX() {
        return (Window.width - _dlg_serialport.width) / 2
    }
    function computeDialogY() {
        return (Window.height - _dlg_serialport.height) / 2
    }

    Qaterial.Dialog {
        id: _dlg_serialport
        width: 500
        height: 500
        SerialPortConfigureView {
            anchors.fill: parent
            id: _view_serialport_conf

            onBtnOkClicked: {
                _dlg_serialport.accept()
            }
            onBtnCancelClicked: {
                _dlg_serialport.reject()
            }
        }

        function showDialog(isMultiple) {
            _view_serialport_conf.isMultiConf = isMultiple
            _dlg_serialport.open()
        }

        Component.onCompleted: {
            x = computeDialogX()
            y = computeDialogY()
        }
    }

}
