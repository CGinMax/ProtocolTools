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
//        Loader {
//            id: loader_err_icon
//            asynchronous: true
//            sourceComponent: Qaterial.ColorIcon {
//                id: icon_inner
//                property bool hovered: false
//                visible: error_message !== ""
//                source: "image://faicon/times-circle"
//                color: "red"
//                ToolTip {
//                    visible: parent.hovered && parent.visible
//                    text: error_message
//                }
//            }
//            Layout.leftMargin: 5
//            Layout.preferredWidth: 20
//            Layout.preferredHeight: 20
//            MouseArea {
//                anchors.fill: parent
//                hoverEnabled: true
//                onEntered: parent.item.hovered = true
//                onExited: parent.item.hovered = false
//            }
//        }

        Qaterial.Label {
            id: label_name
            text: sensor_name
            font.pixelSize: 18
            font.bold: true
            horizontalAlignment: Text.AlignRight
            Layout.preferredWidth: 90
        }

        Row {
            Loader {
                id: loader_input_address
                asynchronous: true
                sourceComponent: Qaterial.TextField {
                    title: qsTr("Address")
                    text: address
                    validator: IntValidator{ bottom: 1 }
                }
            }

            Loader {
                id: loader_btn_configure_addr
                asynchronous: true
                sourceComponent: LoadingButton {
                    iconSource: "image://faicon/arrow-alt-circle-left"
                    iconSize: 18
                    onClickStarted: {
                        _root.configureSensorAddr(address, parseInt(loader_input_address.item.text))
                    }
                    ToolTip{
                        visible: parent.hovered
                        text: qsTr("Configure sensor address")
                    }
                }
            }

            Loader {
                id: loader_btn_query_addr
                asynchronous: true
                sourceComponent: LoadingButton {
                    iconSource: "image://faicon/search"
                    iconSize: 18
                    onClickStarted: {
                        _root.querySensorAddr()
                    }
                    ToolTip {
                        visible: parent.hovered
                        text: qsTr("Query sensor address")
                    }
                }
            }
        }

        RowLayout {
            ColumnLayout {
                Layout.preferredWidth: 80
                Layout.fillHeight: true
                Loader {
                    asynchronous: true
                    Layout.preferredHeight: 30
                    sourceComponent: StateLabel {
                        value: current_status
                        text: current_status_text
                        ToolTip{
                            visible: parent.hovered
                            text: qsTr("Sensor current state")
                        }
                    }
                }
                Loader {
                    asynchronous: true
                    Layout.preferredHeight: 30
                    sourceComponent: StateLabel {
                        value: configured_status
                        text: configured_status_text
                        ToolTip{
                            visible: parent.hovered
                            text: qsTr("Sensor configed state")
                        }
                    }
                }
            }
            Loader {
                id: loader_btn_query_state
                asynchronous: true
                sourceComponent: LoadingButton {
                    iconSource: "image://faicon/search"
                    iconSize: 18
                    onClickStarted: {
                        emit: _root.querySensorStatus(address)
                    }
                    ToolTip{
                        visible: parent.hovered
                        text: qsTr("Query sensor status")
                    }
                }
            }
        }
        Row {
            Loader {
                id: loader_cbb_configure_state
                asynchronous: true
                sourceComponent: Qaterial.ComboBox {
                    borderColor: "gray"
                    model: [qsTr("Open"), qsTr("Close"), qsTr("Unconfigured")]
                }
            }


            Loader {
                id: loader_btn_configure_state
                asynchronous: true
                sourceComponent: LoadingButton {
                    iconSource: "image://faicon/arrow-alt-circle-left"
                    iconSize: 18
                    onClickStarted: {
                        emit: _root.configureSensorStatus(address,
                                                          loader_cbb_configure_state.item.currentIndex !== 2 ?
                                                          loader_cbb_configure_state.item.currentIndex : 0xFF)
                    }
                    ToolTip{
                        visible: parent.hovered
                        text: qsTr("Configure sensor state")
                    }
                }
            }
        }

        RowLayout {
            Column {
                RowLayout {
                    spacing: 10
                    Chip {
                        id: chip_hardware_version
                        text: hardware_version

                    }
                    Chip {
                        id: chip_software_version
                        text: software_version
                    }
                    Loader {
                        id: loader_btn_query_version
                        asynchronous: true
                        Layout.preferredWidth: 32
                        Layout.preferredHeight: 32
                        sourceComponent: LoadingButton {
                            iconSource: "image://faicon/search"
                            iconSize: 18
                            onClickStarted: {
                                emit: _root.querySensorVersion(address)
                            }
                            ToolTip{
                                visible: parent.hovered
                                text: qsTr("Query sensor version")
                            }
                        }
                    }
                }

                Chip {
                    text: qsTr("Product Description")
                    ToolTip {
                        visible: parent.hovered && product_description !== ""
                        text: product_description
                    }
                }
            }
        }

        Loader {
            id: loader_btn_delete
            asynchronous: true
            width: 18
            height: 18
            sourceComponent: Qaterial.RoundButton {
                icon.source: "image://faicon/trash-alt"
                icon.width: 18
                icon.height: 18
                onClicked: {
                    list_model.removeSensor(index)
                }
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

    function configureSensorAddr(oldAddr, newAddr){
        if (!_root.gatherController.isConnected()) {
            changeAddressState(false);
            _root.gatherController.alertNotOpen();
            return;
        }
        controller_sensor.configureSensorAddress(oldAddr, newAddr, ComConfig.sensorTimeout);
    }

    function querySensorAddr() {
        if (!_root.gatherController.isConnected()) {
            changeQueryAddrState(false);
            _root.gatherController.alertNotOpen();
            return ;
        }
        controller_sensor.querySensorAddr(ComConfig.sensorTimeout);
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
        loader_btn_query_version.item.changeState(success)
    }
    function changeAddressState(success) {
        loader_btn_configure_addr.item.changeState(success)
    }

    function changeQueryAddrState(success) {
        loader_btn_query_addr.item.changeState(success)
    }

    function changeQueryStatusState(success) {
        loader_btn_query_state.item.changeState(success)
    }

    function changeConfigureStatusState(success) {
        loader_btn_configure_state.item.changeState(success)
    }

    SensorController {
        id: controller_sensor
        onQueryVersionCallback: function(result/* success, hardware, software, product*/) {
            if (result.success) {
                list_model.setVersion(index, result.hardware, result.software, result.product);
            }
            changeVersionState(result.success);
        }
        onQueryStateCallback: function(result/*success, curState, confState*/) {
            if (result.success) {
                list_model.setState(index, result.curState, result.confState);
            }
            changeQueryStatusState(result.success);
        }
        onQueryAddrCallback: function(result/*success, addr*/) {
            if (result.success) {
                list_model.setAddress(index, result.addr);
            }
            changeQueryAddrState(result.success);
        }

        onConfigureAddressCallback: function(result/*success, oldAddr, newAddr*/){
            if (result.success) {
                list_model.setAddress(index, result.newAddr);
                _root.querySensorStatus(result.newAddr);
            }
            else {
                loader_input_address.item.text = result.oldAddr;
                _root.querySensorStatus(result.oldAddr);
            }

            changeAddressState(result.success);
        }
        onConfigureStateCallback: function(result/*success, state*/) {
            if (result.success) {
                list_model.setConfState(index, result.state);
            }
            changeConfigureStatusState(result.success);
        }
    }
}
