import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qaterial 1.0 as Qaterial

import PressPlateTools 1.0
import "../components"
import "../data"
Qaterial.GroupBox {
    id: _root
    title: qsTr("Gather Configuration")
    inlineTitle: true
    Layout.fillWidth: true
    Layout.preferredWidth: 500
    Layout.fillHeight: true

    property bool isStarted: false
    property alias gatherController: controller_gather

    ColumnLayout {

        Row {
            Qaterial.TextField {
                id: input_address
                title: qsTr("Address")
                text: "1"
                validator: IntValidator{ bottom: 1 }

            }
            LoadingButton {
                id: btn_configure_address
                iconSource: "image://faicon/arrow-alt-circle-left"
                iconSize: 18
                ToolTip{
                    visible: parent.hovered
                    text: qsTr("Configure gather address")
                }
            }

            Qaterial.TextField {
                id: input_sensor_count
                title: qsTr("Sensor Count")
                text: "0"
                validator: IntValidator{ bottom: 0 }

            }
            LoadingButton {
                id: btn_configure_sensor_count
                iconSource: "image://faicon/arrow-alt-circle-left"
                iconSize: 18
                ToolTip{
                    visible: parent.hovered
                    text: qsTr("Configure gather count")
                }
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            Row {
                id: layout_version
                spacing: 5

                Layout.fillWidth: true
                Layout.preferredWidth: 200
                LabelTile {
                    id: label_hardware
                    title: qsTr("Hardware Version")
                    text: "0.0"


                }
                LabelTile {
                    id: label_software
                    title: qsTr("Software Version")
                    text: "0.0"

                }
                LoadingButton {
                    id: btn_query_version
                    iconSource: "image://faicon/search"
                    iconSize: 18
                    ToolTip{
                        visible: parent.hovered
                        text: qsTr("Query gather version")
                    }
                }
            }
            LabelTile {
                id: label_product
                title: qsTr("Product Description")
                text: qsTr("None")
                Layout.fillWidth: true
            }
        }
    }


    function queryVersion() {
        if (!controller_gather.isConnected()) {
            btn_query_version.changeState(false)
            controller_gather.alertNotOpen()
            return;
        }
        controller_gather.queryGatherVersion(parseInt(input_address.text), ComConfig.gatherTimeout)
    }

    function configureAddress() {
        if (!controller_gather.isConnected()) {
            btn_configure_address.changeState(false)
            controller_gather.alertNotOpen()
            return;
        }
        controller_gather.configureGatherAddress(parseInt(input_address.text), ComConfig.gatherTimeout)

    }

    function configureSensorCount() {
        if (!controller_gather.isConnected()) {
            btn_configure_sensor_count.changeState(false)
            controller_gather.alertNotOpen()
            return;
        }
        controller_gather.configureSensorCount(parseInt(input_address.text), parseInt(input_sensor_count.text), ComConfig.gatherTimeout)
    }

    function toggleCommunication(portParam) {
        if (controller_gather.isConnected()) {
            controller_gather.stopCommunication();
        } else if (!controller_gather.startCommunication(portParam)) {
            Qaterial.SnackbarManager.show({text: qsTr("Start communication failed!")});
            return;
        }
        _root.isStarted = !_root.isStarted;
    }


    GatherController{
        id: controller_gather
        onQueryVersionCallback: function(result/*success, hardware, software, product*/) {
            if (result.success) {
                label_hardware.text = result.hardware
                label_software.text = result.software
                label_product.text = result.product
            }

            btn_query_version.changeState(result.success)
        }
        onConfigureAddressCallback: function(result /*success, addr*/) {
            if (result.success) {
                input_address.text = result.addr
            }
            btn_configure_address.changeState(result.success)
        }
        onConfigureCountCallback: function(result /*success, count*/) {
            if (result.success) {
                input_sensor_count.text = result.count
            }
            btn_configure_sensor_count.changeState(result.success)
        }
        function alertNotOpen() {
            Qaterial.SnackbarManager.show({text: qsTr("Communication not open!Can not operate!")})
        }
    } // GatherController

    Component.onCompleted: {
        btn_configure_address.clicked.connect(_root.configureAddress)
        btn_configure_sensor_count.clickStarted.connect(_root.configureSensorCount)
        btn_query_version.clickStarted.connect(_root.queryVersion)
    }
}
