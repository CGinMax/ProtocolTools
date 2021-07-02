import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qaterial 1.0 as Qaterial

import PressPlateTools 1.0
import "../components"

Qaterial.Card {
    id: _root

    property var list_model: null

    RowLayout {
        anchors.fill: parent
        Qaterial.Label {
            id: label_name
            text: sensor_name
            font.pixelSize: 18
            font.bold: true

            Layout.leftMargin: 5
        }


        Qaterial.TextField {
            id: input_address
            title: qsTr("Address")
            text: address
            validator: IntValidator{ bottom: 1 }
            trailingVisible: focus
            trailingContent: Qaterial.TextFieldIconButton {
                icon.source: "image://faicon/arrow-alt-circle-left"
                icon.width: 24
                icon.height: 24
                onClicked: {
                    _root.configureAddress(input_address.text)
                }
            }
        }

        Qaterial.FlatButton {
            id: btn_query_status
            text: "query"
            onClicked: {
                _root.queryStatus()
            }
        }

        Qaterial.FlatButton {
            id: btn_configure_status
            text: "configure"
            onClicked: {

            }
        }

        RowLayout {
            Chip {
                id: chip_hardware_version
                text: hardware_version

            }
            Chip {
                id: chip_software_version
                text: software_version
            }
            LoadingButton {
                id: btn_query_version
                iconSource: "image://faicon/search"
                iconSize: 18
                onClickStarted: {
                    _root.queryVersion()
                }

            }
        }

        Qaterial.RoundButton {
            id: btn_delete
            icon.source: "image://faicon/trash"
            icon.width: 18
            icon.height: 18
            icon.color: "red"
            onClicked: {
                list_model.removeSensor(index)
            }
        }
    }

//    function queryVersion() {
//        if (checkConnected()) {
//            controller.querySensorVersion(address, timeout)
//        }
//    }

//    function queryStatus() {
//        if (checkConnected()) {
//            controller.querySensorStatus(address, timeout)
//        }
//    }

//    function configureStatus(status) {
//        if (checkConnected()) {
//            controller.configureSensorStatus(address, status, timeout)
//        }
//    }

//    function configureAddress(addr) {
//        if (checkConnected()) {
//            controller.configureSensorAddress(addr, timeout)
//        }
//    }

//    function checkConnected() {
//        if (!controller.isConnected()) {
//            Qaterial.SnackbarManager.show({
//                text: "Communication not open!Can not operate!"
//            })
//            return false;
//        }
//        return true;
//    }

}
