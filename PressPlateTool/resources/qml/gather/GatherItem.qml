import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qaterial 1.0 as Qaterial

import "../components"

Qaterial.Card {
    id: _root

    signal queryVersionClicked()
    signal configureAddrClicked(int addr)
    signal configureSensorCounterClicked(int count)
    signal toggleCommunication()

    signal deleteItem()

    property bool isStarted: false

    x: 10
    width: parent.width - 40
    height: 200
    elevation: 8.0
    elevationOnHovered: true
    outlined: true

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
//    Qaterial.AppBarButton {
//        id: btn_query_version
//        icon.source: "image://faicon/search"
//        icon.width: 18
//        icon.height: 18
//        anchors.verticalCenter: label_software_version.verticalCenter
//        anchors.left: label_software_version.right
//        onClicked: {emit: _root.queryVersionClicked()}
//    }
    LoadingButton {
        id: btn_query_version
        iconSource: "image://faicon/search"
        iconSize: 18
        actionState: query_version_state
        anchors.verticalCenter: label_software_version.verticalCenter
        anchors.left: label_software_version.right
        onClickStarted: {emit: _root.queryVersionClicked()}
    }

    Chip {
        id: label_product_desc
        text: product_description
        anchors.top: label_hardware_version.bottom
        anchors.topMargin: 5
        anchors.left: label_hardware_version.left
    }

    Qaterial.TextField {
        id: input_address
        title: qsTr("Address")
        text: address
        anchors.left: label_name.left
        anchors.top: label_product_desc.bottom
        trailingVisible: focus
        trailingContent: Qaterial.TextFieldIconButton {
            icon.source: "image://faicon/arrow-alt-circle-left"
            icon.width: 24
            icon.height: 24
        }
    }

    Qaterial.TextField {
        id: input_sensor_count
        title: qsTr("Sensor Count")
        text: sensor_count
        anchors.left: input_address.right
        anchors.leftMargin: 5
        anchors.top: input_address.top
        trailingVisible: focus
        trailingContent: Qaterial.TextFieldIconButton {
            icon.width: 24
            icon.height: 24
            icon.source: "image://faicon/arrow-alt-circle-left"
        }

    }

    Qaterial.FlatButton {
        id: btn_run
        text: isStarted ? qsTr("Close") : qsTr("Open")
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        onClicked: {emit: _root.toggleCommunication()}
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
            onClicked: {emit: _root.deleteItem()}
        }

    }

}
