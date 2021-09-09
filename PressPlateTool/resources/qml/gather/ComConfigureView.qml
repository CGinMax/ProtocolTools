import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Qaterial 1.0 as Qaterial

import PressPlateTools 1.0

import "../data"
Qaterial.GroupBox {
    id: _root
    title: qsTr("Communication configuration")
    inlineTitle: true
    property int labelWidth: 60
    property bool isStarted: false

    signal toggleCommunication(var portParam)

    implicitWidth: 400
    implicitHeight: 400

    ColumnLayout {
        RowLayout {
            spacing: 20
            Layout.alignment: Qt.AlignLeft
            Qaterial.Label {
                Layout.preferredWidth: _root.labelWidth
                font.pixelSize: 16
                text: qsTr("Device List")
            }

            Qaterial.ComboBox {
                id: _cbb_devices
//                Layout.fillWidth: true
                borderColor: "gray"
                model: ListModel {
                    id: model_devices
                }
            }

            Qaterial.OutlineButton {
//                Layout.fillWidth: true
                text: qsTr("Refresh")
                onClicked: _root.refreshDevices()
            }
            Qaterial.ToolSeparator {

            }

            Qaterial.Label{
                Layout.preferredWidth: _root.labelWidth
                font.pixelSize: 16
                text: qsTr("Buad Rate")
            }
            Qaterial.ComboBox {
                id: _cbb_baudrate

//                Layout.fillWidth: true
                borderColor: "gray"

                model: ListModel{
                    id: model_baudrate
                }
            }

        }

        RowLayout {
            spacing: 20
            Layout.alignment: Qt.AlignLeft
            Qaterial.TextField {
                title: qsTr("Gather Timeout Time")
                text: ComConfig.gatherTimeout
                suffixText: qsTr("ms")
                validator: IntValidator{ bottom: 1 }
                onTextChanged: {
                    ComConfig.gatherTimeout = parseInt(text);
                }
                Layout.fillWidth: true
            }
            Qaterial.TextField {
                title: qsTr("Sensor Timeout Time")
                text: ComConfig.sensorTimeout
                suffixText: qsTr("ms")
                validator: IntValidator{ bottom: 1 }
                onTextChanged: {
                    ComConfig.sensorTimeout = parseInt(text);
                }
                Layout.fillWidth: true
            }
            Qaterial.RawMaterialButton {
                id: btn_start
                text: _root.isStarted ? qsTr("Stop") : qsTr("Start")
                flat: _root.isStarted
                outlined: _root.isStarted
                Layout.fillWidth: true
            }

        }
    }


    QmlSerialPortHelper{
        id: _serialport_helper
    }

    function refreshDevices() {
        model_devices.clear();
        var ports = _serialport_helper.availablePorts();
        for (var i = 0; i < ports.length; i++) {
            model_devices.append({text: ports[i]});
        }

        _cbb_devices.currentIndex = 0;
    }

    function runStart() {
        if (_cbb_devices.currentText === "") {
            Qaterial.SnackbarManager.show({text: qsTr("Error! Serial Port name is invalid!")});
        }

        let portParam = {
            portName: _cbb_devices.currentText,
            baudRate: parseInt(_cbb_baudrate.currentText),
            dataBit: 8,
            stopBit: 1,
            parity: 0,
        };
        emit: _root.toggleCommunication(portParam);
    }


    Component.onCompleted: {
        // init combobox data
        refreshDevices()
        model_baudrate.clear()
        var baudrates = _serialport_helper.standardBaudRates()
        for (var i = 0; i < baudrates.length; i++) {
            model_baudrate.append({text: baudrates[i]})
        }

        _cbb_baudrate.currentIndex = _cbb_baudrate.find("9600")

        // connect signal
        btn_start.clicked.connect(_root.runStart)
    }


}
