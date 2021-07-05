import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import PressPlateTools 1.0
import Qaterial 1.0 as Qaterial

import "../components"

Rectangle {
    id: _root

    property alias gatherController: gather_item.gatherController

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        ComConfigureView {
            id: view_com_configure
            isStarted: gather_item.isStarted
            Layout.fillWidth: true
            Layout.preferredHeight: 150
            onToggleCommunication: function(portParam) {
                gather_item.toggleCommunication(portParam);
            }
        }


        GatherItem {
            id: gather_item
        }
    }

//    RowLayout {
//        anchors.fill: parent
//        anchors.margins: 5

//        GatherItem {
//            id: gather_item
//        }

//        ColumnLayout {
//            Layout.fillWidth: true
//            Qaterial.GroupBox {
//                id: box_serialport
//                title: qsTr("Serial Port Configuration")
//                inlineTitle: true

//                Layout.fillWidth: true
//                SerialPortConfigureView {
//                    id: view_serialport
//                    anchors.fill: parent
//                } // SerialPortConfigureView
//            }

//            Qaterial.GroupBox {
//                id: box_timeout
//                title: qsTr("Timeout Configuration")
//                inlineTitle: true
//                Layout.fillWidth: true
//                Column {
//                    Qaterial.TextField {
//                        title: qsTr("Gather Timeout Time")

//                        text: "12000"
//                    }
//                    Qaterial.TextField {
//                        title: qsTr("Sensor Timeout Time")
//                        text: "12000"
//                    }
//                }
//            }
//            Qaterial.OutlineButton {
//                id: btn_start
//                text: qsTr("Start")
//                Layout.alignment: Qt.AlignRight
//            }
//        }
//    }
//    Component.onCompleted: {
//        btn_start.clicked.connect(gather_item.toggleCommunication)
//    }
} // Rectangle
