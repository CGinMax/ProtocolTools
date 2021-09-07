import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Qaterial 1.0 as Qaterial

import PressPlateTools 1.0

import "../data"
import "../dialog"

Rectangle {
    id: _root

    property var gatherController: null
    Loader {
        id: dialogLoader
        onLoaded: item.open()
    }
    ColumnLayout {

        anchors.fill: parent

        Row {
            Qaterial.Button {
                id: btn_add_one_sensor
                text: qsTr("Add one")
                onClicked: {
                    model_sensor_configure.appendSensors(1)
                    input_end_addr.text = parseInt(input_begin_addr.text) + listview_sensor.count - 1
                }
            }
            Qaterial.Button {
                id: btn_add_multi
                text: qsTr("Add Multiple")
                onClicked: dialogLoader.sourceComponent = _textFieldDialogComponent
                Component {
                    id: _textFieldDialogComponent
                    AddMultiDialog {
                        id: _addMultiDialog
                        onAccepted: {
                            model_sensor_configure.appendSensors(beginNum, count);
                            input_begin_addr.text = beginNum;
                            input_end_addr.text = parseInt(beginNum) + parseInt(count);
                        }
                        onRejected: {}
                        onClosed: dialogLoader.sourceComponent = undefined
                    }

//                    Qaterial.TextFieldDialog {
//                        id: _textFieldDialog
//                        title: qsTr("Sensor Number Configuration")
//                        textTitle: qsTr("Sensor Numbers")
//                        text: "1"
//                        validator: IntValidator{ bottom: 1}
//                        onAccepted: {
//                            model_sensor_configure.appendSensors(parseInt(text))
//                            input_end_addr.text = parseInt(input_begin_addr.text) + listview_sensor.count - 1
//                        }
//                        onRejected: {}
//                        onClosed: dialogLoader.sourceComponent = undefined
//                    }
                }
            }
            Qaterial.Button {
                id: btn_query_all_version
                text: qsTr("Automatic query sensor version")
                enabled: listview_sensor.count !== 0
                onClicked: {
                    if (!_root.gatherController.isConnected()) {
                        _root.gatherController.alertNotOpen()
                        return;
                    }
                    auto_query_dialog.openDialog(qsTr("Querying sensor version.\nQuery sensor address is "), model_sensor_configure.getAddr(0))
                    _root.gatherController.querySensorVersion(0, model_sensor_configure.getAddr(0), ComConfig.sensorTimeout);
                }
            }
            Qaterial.Button {
                id: btn_query_all_status
                text: qsTr("Automatic query sensor status")
                enabled: listview_sensor.count !== 0
                onClicked: {
                    if (!_root.gatherController.isConnected()) {
                        _root.gatherController.alertNotOpen()
                        return;
                    }
                    auto_query_dialog.openDialog(qsTr("Querying sensor state.\nQuery sensor address is "), model_sensor_configure.getAddr(0));
                    _root.gatherController.querySensorState(0, model_sensor_configure.getAddr(0), ComConfig.sensorTimeout);
                }
            }

            Qaterial.RoundButton {
                id: btn_delete_all
                enabled: listview_sensor.count !== 0
                icon.source: "image://faicon/trash"
                icon.width: 18
                icon.height: 18
                icon.color: enabled ? "red" : Qaterial.Style.disabledTextColorLight
                onClicked: dialogLoader.sourceComponent = _alertComponentTitle
                Component {
                    id: _alertComponentTitle
                    Qaterial.AlertDialog {
                        title: qsTr("Information")
                        text: qsTr("Are you sure you want to delete all item?")
                        standardButtons: Dialog.No | Dialog.Ok
                        onAccepted: model_sensor_configure.removeAll()
                        onRejected: {}
                        onClosed: dialogLoader.sourceComponent = undefined
                    }
                }
            }
        }
        Row {
            spacing: 5
            leftPadding: 10
            Qaterial.TextField {
                id: input_begin_addr
                enabled: listview_sensor.count !== 0
                title: qsTr("Begin Address")
                text: "1"
                validator: IntValidator{ bottom: 1 }
                onTextChanged: {
                    input_end_addr.text = parseInt(text) + listview_sensor.count - 1
                }
            }
            Qaterial.TextField {
                id: input_end_addr
                enabled: listview_sensor.count !== 0
                title: qsTr("End Address")
                text: "1"
                validator: IntValidator{ bottom: 1 }
            }
            Qaterial.Button {
                id: btn_configure_all_addr
                enabled: listview_sensor.count !== 0
                text: qsTr("Automatic configure sensor address")
                onClicked: {
                    if (!_root.gatherController.isConnected()) {
                        _root.gatherController.alertNotOpen()
                        return;
                    }
                    auto_query_dialog.openDialog(qsTr("Configuring sensors address.\nConfiguration Address is "), parseInt(input_begin_addr.text));
                    _root.gatherController.configureSensorAddr(0, parseInt(input_begin_addr.text), ComConfig.sensorTimeout);
                }
            }

            Qaterial.ComboBox {
                id: cbb_configure_state
                enabled: listview_sensor.count !== 0
                borderColor: "gray"
                model: [qsTr("Open"), qsTr("Close"), qsTr("Unconfigured")]
                function value() {
                    return (currentIndex < 2 || currentIndex >= 0) ? currentIndex : 0xFF
                }
            }
            Qaterial.Button {
                id: btn_configure_all_state
                enabled: listview_sensor.count !== 0
                text: qsTr("Automatic configure sensor state")
                onClicked: {
                    if (!_root.gatherController.isConnected()) {
                        _root.gatherController.alertNotOpen()
                        return;
                    }
                    auto_query_dialog.openDialog(qsTr("Configuring sensors state.\nConfiguration Sensor Address is "), model_sensor_configure.getAddr(0));
                    _root.gatherController.configureSensorState(0, model_sensor_configure.getAddr(0), cbb_configure_state.value(), ComConfig.sensorTimeout);
                }
            }
        }

        ListView {
            id: listview_sensor
            property int delegateHeight: 80
            clip: true

            Layout.fillWidth: true
            Layout.fillHeight: true
            model: SensorConfigureModel {
                id: model_sensor_configure
            }

            delegate: SensorItem{
                id: delegate_sensor
                x: 10
                elevation: 0
                outlined: true
                width: listview_sensor.width - 20
                height: listview_sensor.delegateHeight
                gatherController: _root.gatherController
                list_model: model_sensor_configure
            }
             ScrollBar.vertical: ScrollBar {
                 background: Rectangle{
                     color: "transparent"
                 }
             }
        }
    }
    AutoConfigureComponent{
        id: auto_query_dialog
        width: 500
        height: 300
    }
    Connections {
        target: gatherController
        onConfigureSensorAddrCallback: function(result) {
            if (!auto_query_dialog.isRun) {
                return;
            }
            if (result.success) {
                model_sensor_configure.setAddress(result.index, result.addr);
            } else {
                model_sensor_configure.setErrorMessage(result.index, result.errorMsg);
            }

            auto_query_dialog.addModelData(result.success, model_sensor_configure.getName(result.index));
            result.index++;
            result.addr++;
            if (result.index < listview_sensor.count && result.addr <= parseInt(input_end_addr.text)) {
                _root.gatherController.configureSensorAddr(result.index, result.addr, ComConfig.sensorTimeout);
                auto_query_dialog.updateAddress(result.addr);
            } else {
                auto_query_dialog.finished();
                // query state when finish configure all address
//                _root.gatherController.querySensorState(0, model_sensor_configure.getAddr(0), ComConfig.sensorTimeout);
            }
        }

        onConfigureSensorStateCallback: function(result/*success, index, state*/) {
            if(!auto_query_dialog.isRun){
                return;
            }
            if (result.success){
                model_sensor_configure.setConfState(result.index, result.state);
            } else {
                model_sensor_configure.setErrorMessage(result.index, result.errorMsg)
            }

            auto_query_dialog.addModelData(result.success, model_sensor_configure.getName(result.index));
            result.index++;
            if (result.index < listview_sensor.count) {
                _root.gatherController.configureSensorState(result.index, model_sensor_configure.getAddr(result.index), result.state, ComConfig.sensorTimeout);
                auto_query_dialog.updateAddress(model_sensor_configure.getAddr(result.index));
            } else {
                auto_query_dialog.finished();
            }
        }

        onQuerySensorVersionCallback: function(result/*success, index, hardware, software, product*/) {
            // stop by click cancel
            if (!auto_query_dialog.isRun) {
                return;
            }

            if (result.success) {
                model_sensor_configure.setVersion(result.index, result.hardware, result.software, result.product);
            } else {
                model_sensor_configure.setErrorMessage(result.index, result.errorMsg);
            }

            auto_query_dialog.addModelData(result.success, model_sensor_configure.getName(result.index));

            result.index++;
            if (result.index < listview_sensor.count) {
                _root.gatherController.querySensorVersion(result.index, model_sensor_configure.getAddr(result.index), ComConfig.sensorTimeout);
                auto_query_dialog.updateAddress(model_sensor_configure.getAddr(result.index));
            } else {
                auto_query_dialog.finished();
            }
        }
        onQuerySensorStateCallback: function(result/*success, index, curState, configuredState*/) {
            // stop by click cancel
            if (!auto_query_dialog.isRun) {
                return;
            }

            if (result.success) {
                model_sensor_configure.setState(result.index, result.curState, result.confState);
            } else {
                model_sensor_configure.setErrorMessage(result.index, result.errorMsg);
            }

            auto_query_dialog.addModelData(result.success, model_sensor_configure.getName(result.index));

            result.index++;
            if (result.index < listview_sensor.count) {
                _root.gatherController.querySensorState(result.index, model_sensor_configure.getAddr(result.index), ComConfig.sensorTimeout);
                auto_query_dialog.updateAddress(model_sensor_configure.getAddr(result.index));
            } else {
                auto_query_dialog.finished();
            }
        }
    }
}
