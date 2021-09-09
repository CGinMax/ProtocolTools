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
    property int mescOfDay: 86400000 // 1000 * 60 * 60 * 24
    color: "#C2F5F5F5"
    Loader {
        id: dialogLoader
        onLoaded: item.open()
    }
    ColumnLayout {

        anchors.fill: parent

        RowLayout {
            Layout.leftMargin: 12
            Layout.topMargin: 24
            Column {
                Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
                Layout.fillWidth: true
                spacing: 12
                Qaterial.Label {
                    text: qsTr("Sensor Configuration")
                    font.bold: true
                    textType: Qaterial.Style.TextType.Heading

                }
                Qaterial.Label {
                    text: qsTr("Configurate and query sensor information by single or multiple")
                    textType: Qaterial.Style.TextType.Subheading
                    color: Qaterial.Style.disabledTextColor()
                }
            }
            Qaterial.RawMaterialButton {
                Layout.alignment: Qt.AlignRight | Qt.AlignBottom
                text: qsTr("Add")
                icon.source: "image://faicon/plus"
                onClicked: dialogLoader.sourceComponent = _textFieldDialogComponent
                Component {
                    id: _textFieldDialogComponent
                    AddMultiDialog {
                        id: _addMultiDialog
                        onAccepted: {
                            model_sensor_configure.appendSensors(beginNum, count);
                            input_begin_addr.text = beginNum;
                            input_end_addr.text = parseInt(beginNum) + parseInt(count) - 1;
                        }
                        onRejected: {}
                        onClosed: dialogLoader.sourceComponent = undefined
                    }
                }
            }

            Qaterial.RoundButton {
                Layout.alignment: Qt.AlignRight | Qt.AlignBottom
                enabled: listview_sensor.count !== 0
                icon.source: "image://faicon/trash"
                icon.width: 18
                icon.height: 18
                icon.color: enabled ? "red" : Qaterial.Style.disabledTextColorLight
                onClicked: dialogLoader.sourceComponent = _alertComponentTitle
                Component {
                    id: _alertComponentTitle
                    Qaterial.AlertDialog {
                        id: _alertDialog
                        title: qsTr("Information")
                        text: qsTr("Are you sure you want to delete all item?")
                        footer: RowLayout {
                            Qaterial.RawMaterialButton {
                                Layout.alignment: Qt.AlignCenter
                                text: qsTr("Confirm")
                                backgroundColor: "red"
                                onClicked: _alertDialog.accept()
                            }
                            Qaterial.FlatButton {
                                Layout.alignment: Qt.AlignCenter
                                text: qsTr("Cancel")
                                onClicked: _alertDialog.reject()
                            }
                        }

                        onAccepted: model_sensor_configure.removeAll()
                        onRejected: {}
                        onClosed: dialogLoader.sourceComponent = undefined
                    }
                }
            }
        }

        Qaterial.HorizontalLineSeparator {
            Layout.fillWidth: true
            Layout.topMargin: 12
            Layout.leftMargin: 12
            Layout.rightMargin: 12
        }

        Column {
            spacing: 12
            Layout.leftMargin: 12
            Layout.topMargin: 18
            Layout.fillWidth: true
            Row {
                spacing: 12
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
                        auto_query_dialog.closeCallback = function() {
                            _root.gatherController.cancelLongConfigAddr();
                        }

                        const beginAddr = parseInt(input_begin_addr.text);
                        _root.gatherController.configureSensorAddr(model_sensor_configure.getIndexByAddr(beginAddr), beginAddr, _root.mescOfDay);
                    }
                }
                Qaterial.ToolSeparator {

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
                        auto_query_dialog.openDialog(qsTr("Configuring sensors state.\nConfiguration sensor state is "), model_sensor_configure.getAddr(0));
                        auto_query_dialog.closeCallback = null;
                        _root.gatherController.configureSensorState(0, model_sensor_configure.getAddr(0), cbb_configure_state.value(), ComConfig.sensorTimeout);
                    }
                }
            } // configure addr and status

            Row {
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
                        auto_query_dialog.closeCallback = null;
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
                        auto_query_dialog.closeCallback = null;
                        _root.gatherController.querySensorState(0, model_sensor_configure.getAddr(0), ComConfig.sensorTimeout);
                    }
                }
            }

        }
        ListView {
            id: listview_sensor
            property int delegateHeight: 80
            clip: true
            //            layer.enabled: count !== 0
            //            layer.effect: Qaterial.ElevationEffect
            //            {
            //                elevation: 1
            //            } // ElevationEffect

            //            contentItem: Rectangle{
            //                color: "white"
            //            }
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
        // 配置地址结果回调
        onConfigureSensorAddrCallback: function(result) {
            if (!auto_query_dialog.isRun) {
                return;
            }
            if (result.success) {
                model_sensor_configure.setAddress(result.index, result.addr);
            }
            auto_query_dialog.addModelData(result.success, model_sensor_configure.getName(result.index));
            result.addr++;
            if (result.addr <= parseInt(input_end_addr.text)) {
                _root.gatherController.configureSensorAddr(model_sensor_configure.getIndexByAddr(result.addr), result.addr, _root.mescOfDay);
                auto_query_dialog.updateAddress(result.addr);
            } else {
                auto_query_dialog.finished();
                // query state when finish configure all address
                _root.gatherController.exitConfigureState(0, 1000);
            }
        }

        // 配置状态结果回调
        onConfigureSensorStateCallback: function(result/*success, index, state*/) {
            if(!auto_query_dialog.isRun){
                return;
            }
            if (result.success){
                model_sensor_configure.setConfState(result.index, result.state);
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

        // 查询版本结果回调
        onQuerySensorVersionCallback: function(result/*success, index, hardware, software, product*/) {
            // stop by click cancel
            if (!auto_query_dialog.isRun) {
                return;
            }

            if (result.success) {
                model_sensor_configure.setVersion(result.index, result.hardware, result.software, result.product);
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

        // 查询状态结果回调
        onQuerySensorStateCallback: function(result/*success, index, curState, configuredState*/) {
            // stop by click cancel
            if (!auto_query_dialog.isRun) {
                return;
            }

            if (result.success) {
                model_sensor_configure.setState(result.index, result.curState, result.confState);
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
