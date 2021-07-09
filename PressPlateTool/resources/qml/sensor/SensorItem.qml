import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qaterial 1.0 as Qaterial

import PressPlateTools 1.0
import "../components"
import "../data"

Qaterial.Card {
    id: _root

    property var list_model: null
    property alias gatherController: controller_sensor.gatherController

    RowLayout {
        anchors.fill: parent
        Qaterial.Label {
            id: label_name
            text: sensor_name
            font.pixelSize: 18
            font.bold: true

            Layout.leftMargin: 5
        }

        Row {
            Qaterial.TextField {
                id: input_address
                title: qsTr("Address")
                text: address
                validator: IntValidator{ bottom: 1 }
            }
            LoadingButton {
                id: btn_configure_addr
                iconSource: "image://faicon/arrow-alt-circle-left"
                iconSize: 18
                onClickStarted: {
                    _root.configureSensorAddr(parseInt(input_address.text))
                }
                ToolTip{
                    visible: parent.hovered
                    text: qsTr("Configure sensor address")
                }
            }
        }

        RowLayout {
            ColumnLayout {
                Layout.preferredWidth: 80
                Layout.fillHeight: true
                StateLabel {
                    Layout.preferredHeight: 30
                    value: current_status
                    text: current_status_text
                    ToolTip{
                        visible: parent.hovered
                        text: qsTr("Sensor current state")
                    }
                }
                StateLabel {
                    Layout.preferredHeight: 30
                    value: configured_status
                    text: configured_status_text
                    ToolTip{
                        visible: parent.hovered
                        text: qsTr("Sensor configed state")
                    }
                }
            }
            LoadingButton {
                id: btn_query_status
                iconSource: "image://faicon/search"
                iconSize: 18
                onClickStarted: {
                    emit: _root.querySensorStatus(parseInt(input_address.text))
                }
                ToolTip{
                    visible: parent.hovered
                    text: qsTr("Query sensor status")
                }
            }
        }
        Row {
            Qaterial.ComboBox {
                id: cbb_configure_status
                borderColor: "gray"
                model: [qsTr("Open"), qsTr("Close"), qsTr("Unconfigured")]
            }
            LoadingButton {
                id: btn_configure_state
                iconSource: "image://faicon/arrow-alt-circle-left"
                iconSize: 18
                onClickStarted: {
                    emit: _root.configureSensorStatus(parseInt(input_address.text), cbb_configure_status.currentIndex != 2 ? cbb_configure_status.currentIndex : 0xFF)
                }
                ToolTip{
                    visible: parent.hovered
                    text: qsTr("Configure sensor state")
                }
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
                    emit: _root.querySensorVersion(parseInt(input_address.text))
                }
                ToolTip{
                    visible: parent.hovered
                    text: qsTr("Query sensor version")
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

    function querySensorVersion(addr) {
        if (!_root.gatherController.isConnected()) {
            changeVersionState(false);
            _root.gatherController.alertNotOpen();
            return;
        }
        controller_sensor.querySensorVersion(addr, ComConfig.sensorTimeout);
    }

    function configureSensorAddr(addr){
        if (!_root.gatherController.isConnected()) {
            changeAddressState(false);
            _root.gatherController.alertNotOpen();
            return;
        }
        controller_sensor.configureSensorAddress(addr, ComConfig.sensorTimeout);
    }
    function querySensorStatus(addr){
        if (!_root.gatherController.isConnected()) {
            changeQueryStatusState(false)
            _root.gatherController.alertNotOpen();
            return;
        }
        controller_sensor.querySensorStatus(addr, ComConfig.sensorTimeout)
    }
    function configureSensorStatus(addr, state) {
        if (!_root.gatherController.isConnected()) {
            changeConfigureStatusState(false)
            _root.gatherController.alertNotOpen();
            return;
        }
        controller_sensor.configureSensorStatus(addr, state, ComConfig.sensorTimeout)
    }

    function changeVersionState(success) {
        btn_query_version.changeState(success)
    }
    function changeAddressState(success) {
        btn_configure_addr.changeState(success)
    }

    function changeQueryStatusState(success) {
        btn_query_status.changeState(success)
    }

    function changeConfigureStatusState(success) {
        btn_configure_state.changeState(success)
    }

    SensorController {
        id: controller_sensor
        onQueryVersionCallback: function(success, hardware, software, product) {
            if (success) {
                list_model.setVersion(index, hardware, software, product);
            }
            changeVersionState(success);
        }
        onQueryStateCallback: function(success, curState, confState) {
            if (success) {
                list_model.setState(index, curState, confState);
            }
            changeQueryStatusState(success);
        }
        onConfigureAddressCallback: function(success, addr){
            if (success) {
                list_model.setAddress(index, addr);
            }
            changeAddressState(success);
        }
        onConfigureStateCallback: function(success, state) {
            if (success) {
                list_model.setConfState(index, state);
            }
            changeConfigureStatusState(success);
        }
    }
}
