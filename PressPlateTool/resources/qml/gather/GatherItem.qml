import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qaterial 1.0 as Qaterial

import PressPlateTools 1.0
import "../components"

Qaterial.Card {
    id: _root

    property var list_model: undefined

    property bool isStarted: false
    property alias gatherController: controller_gather

    Qaterial.OutlineButton {
        id: btn_more
        icon.color: "black"
        width: 42
        height: 42
        icon.width: 20
        icon.height: 20
        icon.source: "image://faicon/ellipsis-h"
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.rightMargin: -5
        anchors.topMargin: -5
        outlined: hovered
        onClicked: {
            popup_menu.open()
        }
    }

    Text {
        id: label_name
        text: gather_name
        font.pixelSize: 22
        font.bold: true
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
    } // Label


    Chip {
        id: label_hardware_version
        text: hardware_version
        anchors.top: label_name.bottom
        anchors.topMargin: 5
        anchors.left: label_name.left
    }
    Chip {
        id: label_software_version
        text: software_version
        anchors.left: label_hardware_version.right
        anchors.leftMargin: 5
        anchors.top: label_hardware_version.top
    }

    LoadingButton {
        id: btn_query_version
        iconSource: "image://faicon/search"
        iconSize: 18
        anchors.verticalCenter: label_software_version.verticalCenter
        anchors.left: label_software_version.right
        onClickStarted: {
            _root.queryVersion()
        }
    }

    Chip {
        id: label_product_desc
        text: product_description
        maxWidth: _root.width - 20
        anchors.top: label_hardware_version.bottom
        anchors.topMargin: 5
        anchors.left: label_hardware_version.left
    }

    Qaterial.TextField {
        id: input_address
        title: qsTr("Address")
        text: address
        validator: IntValidator{ bottom: 1 }
        anchors.left: label_name.left
        anchors.top: label_product_desc.bottom
        trailingVisible: focus
        trailingContent: Qaterial.TextFieldIconButton {
            icon.source: "image://faicon/arrow-alt-circle-left"
            icon.width: 24
            icon.height: 24
            onClicked: {
                _root.configureAddress(input_address.text)
            }
        }
    }

    Qaterial.TextField {
        id: input_sensor_count
        title: qsTr("Sensor Count")
        text: sensor_count
        validator: IntValidator{ bottom: 0 }
        anchors.left: input_address.right
        anchors.leftMargin: 5
        anchors.top: input_address.top
        trailingVisible: focus
        trailingContent: LoadingButton {
            id: btn_configure_sensor_count
            iconSize: 20
            iconSource: "image://faicon/arrow-alt-circle-left"
            onClickStarted: {
                _root.configureSensorCount(parseInt(input_sensor_count.text))
            }
        }
    }

    Qaterial.FlatButton {
        id: btn_run
        text: isStarted ? qsTr("Close") : qsTr("Open")
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        onClicked: {
            toggleCommunication()
        }
    }

    Qaterial.Menu {
        id: popup_menu
        x: btn_more.x
        y: btn_more.y + btn_more.height
        width: 102
        focus: true
        closePolicy: Popup.CloseOnPressOutsideParent | Popup.CloseOnEscape

        Qaterial.MenuItem {
            id: btn_del_one
            text: qsTr("Delete")
            onClicked: {
                deleteItem()
            }
        }
    }



    function queryVersion() {
        if (!controller_gather.isConnected()) {
            Qaterial.SnackbarManager.show({
                text: "Communication not open!Can not operate!"
            })
            return;
        }
        controller_gather.queryGatherVersion(address, timeout)
    }

    function configureAddress(addr) {
        if (!controller_gather.isConnected()) {
            Qaterial.SnackbarManager.show({
                text: "Communication not open!Can not operate!"
            })
            return;
        }
        controller_gather.configureGatherAddress(addr, timeout)
    }

    function configureSensorCount(count) {
        if (!controller_gather.isConnected()) {
            Qaterial.SnackbarManager.show({
                text: "Communication not open!Can not operate!"
            })
            return;
        }
        controller_gather.configureSensorCount(address, count, timeout)
    }

    function toggleCommunication() {
        if (controller_gather.isConnected()) {
            controller_gather.stopCommunication()
            return ;
        } else if (!controller_gather.startCommunication(list_model.portParam(index))) {
             console.log('gather ' + index + 'start failed')
        } else {
            isStarted = !isStarted
        }
    }

    function deleteItem() {
        if (controller_gather.isConnected()) {
            console.log('delete failed!connected...');
            return;
        }

        list_model.removeGather(index)
    }

    GatherController{
        id: controller_gather
        onQueryVersionCallback: function(success, hardware, software, product) {
            if (success) {
                list_model.updateVersion(index, hardware, software, product)
            }

            btn_query_version.changeState(success)
        }
        onConfigureAddressCallback: function(success, addr) {
            if (success) {
                list_model.updateAddress(index, addr)
            }
        }
        onConfigureCountCallback: function(success, count) {
            if (success) {
                list_model.updateSensorCount(index, count)
            }
            btn_configure_sensor_count.changeState(success)
        }
    } // GatherController
}
