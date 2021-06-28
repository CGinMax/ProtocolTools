import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Qaterial 1.0 as Qaterial

import PressPlateTools 1.0

Rectangle {
    id: _root
    property bool isMultiConf: false
    property bool isInWindow: true
    property int gatherCount: 1
    property var portParam: undefined
    signal btnOkClicked()
    signal btnCancelClicked()

    implicitWidth: 400
    implicitHeight: 400

    ColumnLayout {
        anchors.fill: parent
        Qaterial.TextField {
            id: input_gather_number
            Layout.fillWidth: true
            visible: _root.isMultiConf
            title: qsTr("Gather number")
            text: gatherCount.toString()
            onTextChanged: {
                if (input_gather_number.text === "") {
                    gatherCount = 0
                    return;
                }
                gatherCount = parseInt(input_gather_number.text)
            }
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
                id: cbb_data_bit
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
                id: cbb_stop_bit
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
                id: cbb_parity
                Layout.fillWidth: true
                flat: false
                model: [
                    qsTr("None"),
                    qsTr("Even Parity"),
                    qsTr("Odd Parity"),
                    qsTr("Space Parity"),
                    qsTr("Mark Parity")
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
        var ports = _serialport_helper.availablePorts()
        for (var i = 0; i < ports.length; i++) {
            model_devices.append({text: ports[i]})
        }

        _cbb_devices.currentIndex = 0
    }

    function getPortParam() {
        // TODO(shijm): fix it value
        var portParam = {
            portName: _cbb_devices.currentText,
            baudRate: parseInt(_cbb_baudrate.currentText),
            dataBit: parseInt(cbb_data_bit.currentText),
            stopBit: parseInt(cbb_stop_bit.currentText),
            parity: cbb_parity.currentIndex
        }
        return portParam
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
