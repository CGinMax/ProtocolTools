import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Qaterial 1.0 as Qaterial

import PressPlateTools 1.0

Rectangle {
    id: _root
    property bool isMultiConf: false
    property bool isInWindow: true
    signal btnOkClicked()
    signal btnCancelClicked()

    implicitWidth: 400
    implicitHeight: 400

    ColumnLayout {
        anchors.fill: parent
        Qaterial.TextField {
            Layout.fillWidth: true
            visible: _root.isMultiConf
            title: qsTr("Gather number")
        }


        RowLayout {
            Layout.fillWidth: true

            Qaterial.Label {
                Layout.fillWidth: true
                text: qsTr("Device List")
            }

            Qaterial.ComboBox {
                id: _cbb_devices

                Layout.fillWidth: true

                flat: false
                elevation: 6
                model: ListModel {
                    id: model_devices
                }
            }

            Qaterial.Button {
                Layout.fillWidth: true
                text: qsTr("Refresh")
                onClicked: _root.refreshDevices()
            }
        }

        RowLayout {
            Qaterial.Label{
                Layout.fillWidth: true
                text: qsTr("Buad rate")
            }
            Qaterial.ComboBox {
                id: _cbb_baudrate

                Layout.fillWidth: true

                flat: false
                model: ListModel{
                    id: model_baudrate
                }
            }

        }

        RowLayout {
            Layout.fillWidth: true
            Qaterial.Label{
                text: qsTr("Data bit")
            }
            Qaterial.ComboBox {
                Layout.fillWidth: true
                flat: false
                model: [8, 7, 6, 5]
            }

        }

        RowLayout {
            Layout.fillWidth: true
            Qaterial.Label{
                Layout.fillWidth: true
                text: qsTr("Stop bit")
            }
            Qaterial.ComboBox {
                Layout.fillWidth: true
                flat: false
                model: [1, 1.5, 2]
            }

        }

        RowLayout {
            Layout.fillWidth: true
            Qaterial.Label{
                Layout.fillWidth: true
                text: qsTr("Parity")
            }
            Qaterial.ComboBox {
                Layout.fillWidth: true
                flat: false
                contentItem: Item{}
                model: [
                    "No Parity",
                    "Even Parity",
                    "Odd Parity",
                    "Space Parity",
                    "Mark Parity"
                ]
            }

        }

        RowLayout {
            visible: _root.isInWindow
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignCenter
            Qaterial.Button {
                id: _btn_ok
                text: qsTr("Ok")
                onClicked: {
                    emit: _root.btnOkClicked()
                }
            }
            Qaterial.Button {
                id: _btn_cancel
                text: qsTr("Cancel")

                onClicked: {
                    emit: _root.btnCancelClicked()
                }
            }
        }

    }

    QmlSerialPortHelper{
        id: _serialport_helper
    }

    function refreshDevices() {
        model_devices.clear()
        _serialport_helper.availablePorts().forEach((device) => model_devices.append({text: device}))
        _cbb_devices.currentIndex = 0
    }

    Component.onCompleted: {
        refreshDevices()
        model_baudrate.clear()
        _serialport_helper.standardBaudRates().forEach((baudrate) => model_baudrate.append({text: baudrate}))
        _cbb_baudrate.currentIndex = _cbb_baudrate.find("9600")
    }


}
