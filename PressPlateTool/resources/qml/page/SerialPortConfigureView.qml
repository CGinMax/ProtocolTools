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
    property int labelWidth: 100
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
            validator: IntValidator{ bottom: 1}
            onTextChanged: {
                gatherCount = parseInt(input_gather_number.text)
            }
        }


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
            Qaterial.FlatButton {
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
