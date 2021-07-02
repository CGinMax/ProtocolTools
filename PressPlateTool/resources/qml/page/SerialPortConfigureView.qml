import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Qaterial 1.0 as Qaterial

import PressPlateTools 1.0

Rectangle {
    id: _root
    property var portParam: null
    property int labelWidth: 100

    implicitWidth: 400
    implicitHeight: 400

    ColumnLayout {
        anchors.fill: parent


        RowLayout {
            Layout.fillWidth: true

            Qaterial.Label {
                Layout.fillWidth: true
                font.pixelSize: 16
                text: qsTr("Device List")
            }

            Qaterial.ComboBox {
                id: _cbb_devices
                Layout.fillWidth: true
                borderColor: "gray"
//                elevation: 16
                model: ListModel {
                    id: model_devices
                }
            }

            Qaterial.FlatButton {
                Layout.fillWidth: true
                text: qsTr("Refresh")
                onClicked: _root.refreshDevices()
            }
        }

        RowLayout {
            Qaterial.Label{
                Layout.preferredWidth: _root.labelWidth
                font.pixelSize: 16
                text: qsTr("Buad Rate")
            }
            Qaterial.ComboBox {
                id: _cbb_baudrate

                Layout.fillWidth: true
                borderColor: "gray"

                model: ListModel{
                    id: model_baudrate
                }
            }

        }

        RowLayout {
            Qaterial.Label{
                Layout.preferredWidth: _root.labelWidth
                font.pixelSize: 16
                text: qsTr("Data Bit")
            }
            Qaterial.ComboBox {
                id: cbb_data_bit
                Layout.fillWidth: true
                borderColor: "gray"
                model: [8, 7, 6, 5]
            }

        }

        RowLayout {
            Qaterial.Label{
                Layout.preferredWidth: _root.labelWidth
                font.pixelSize: 16
                text: qsTr("Stop Bit")
            }
            Qaterial.ComboBox {
                id: cbb_stop_bit
                Layout.fillWidth: true
                borderColor: "gray"
                model: [1, 1.5, 2]
            }

        }

        RowLayout {
            Qaterial.Label{
                Layout.preferredWidth: _root.labelWidth
                font.pixelSize: 16
                text: qsTr("Parity")
            }
            Qaterial.ComboBox {
                id: cbb_parity
                Layout.fillWidth: true
                borderColor: "gray"
                model: [
                    qsTr("None"),
                    qsTr("Even Parity"),
                    qsTr("Odd Parity"),
                    qsTr("Space Parity"),
                    qsTr("Mark Parity")
                ]
            }

        }
    }

    QmlSerialPortHelper{
        id: _serialport_helper
    }

    function refreshDevices() {
        model_devices.clear()
        var ports = _serialport_helper.availablePorts()
        for (var i = 0; i < ports.length; i++) {
            model_devices.append({text: ports[i]})
        }

        _cbb_devices.currentIndex = 0
    }

    function checkPortParam() {
        // TODO(shijm): fix it value
        if (_cbb_devices.currentText === "") {
            _root.portParam = null
            return false
        }

        _root.portParam = {
            portName: _cbb_devices.currentText,
            baudRate: parseInt(_cbb_baudrate.currentText),
            dataBit: parseInt(cbb_data_bit.currentText),
            stopBit: parseInt(cbb_stop_bit.currentText),
            parity: cbb_parity.currentIndex
        }
        return true
    }


    Component.onCompleted: {
        refreshDevices()
        model_baudrate.clear()
        var baudrates = _serialport_helper.standardBaudRates()
        for (var i = 0; i < baudrates.length; i++) {
            model_baudrate.append({text: baudrates[i]})
        }

        _cbb_baudrate.currentIndex = _cbb_baudrate.find("9600")
    }


}
