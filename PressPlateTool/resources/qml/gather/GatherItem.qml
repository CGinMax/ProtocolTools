import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qaterial 1.0 as Qaterial

Qaterial.Card {
    id: _root

    signal queryVersionClicked()
    signal configureAddrClicked(int addr)
    signal configureSensorCounterClicked(int count)
    signal toggleCommunication()

    signal deleteItem(int index)

    property bool isStarted: false

    x: 10
    width: parent.width - 40
    height: 150
    elevation: 8.0
    elevationOnHovered: true
    outlined: true


    Qaterial.Button {
        id: btn_more
        flat: true

//        width: 40
//        height: 40
//        icon.source: "qrc:/icons/more-vert.png"
//        icon.width: 16
//        icon.height: 16
//        anchors.right: parent.right
//        anchors.top: parent.top
//        onClicked: {
//            popup_menu.open()
//        }
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

    Qaterial.Label {
        id: label_address
        text: qsTr("Address:") + address
        anchors.top: label_name.bottom
        anchors.topMargin: 5
    }
    Qaterial.Button {
        id: btn_configure_addr
        text: qsTr("conf")
        anchors.top: label_address.top
        anchors.left: label_address.right
        anchors.leftMargin: 5
        onClicked: {}
    }

    Qaterial.Label {
        id: label_sensor_count
        text: qsTr("Sensor Count:") + sensor_count
        anchors.top: label_address.bottom
        anchors.topMargin: 5
    }
    Qaterial.Button {
        id: btn_configure_count
        text: qsTr("conf")
        anchors.left: label_sensor_count.right
        anchors.leftMargin: 5
        anchors.top: label_sensor_count.top
        onClicked: {}
    }

    Qaterial.Label {
        id: label_hardware_version
        text: hardware_version
        anchors.top: label_sensor_count.bottom
        anchors.topMargin: 5
    }
    Qaterial.Label {
        id: label_software_version
        text: software_version
        anchors.left: label_hardware_version.right
        anchors.leftMargin: 5
        anchors.top: label_hardware_version.top
    }
    Qaterial.Button {
        id: btn_query_version
        text: qsTr("query")
        anchors.left: label_software_version.right
        anchors.leftMargin: 5
        anchors.top: label_hardware_version.top
        onClicked: {emit: _root.queryVersionClicked()}
    }
    Qaterial.Label {
        id: label_product_desc
        text: product_description
        anchors.top: label_hardware_version.bottom
        anchors.topMargin: 5
    }


    Qaterial.FlatButton {
        id: btn_run
        text: isStarted ? qsTr("Close") : qsTr("Open")
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        onClicked: {emit: _root.toggleCommunication()}
    }

    Popup {
        id: popup_menu
        x: btn_more.x
        y: btn_more.y + btn_more.height
        width: 48
        height: 40
        focus: true
        closePolicy: Popup.CloseOnPressOutsideParent | Popup.CloseOnEscape

        contentItem: Qaterial.FlatButton {
            id: btn_del_one
            flat: true
            text: qsTr("Delete")
            anchors.fill: parent
            onClicked: {emit: _root.deleteItem()}
        }
    }
}
