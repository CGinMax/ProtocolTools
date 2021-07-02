import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import PressPlateTools 1.0
import Qaterial 1.0 as Qaterial

import "../page"
import "../components"

Rectangle {
    id: _root

    property alias gatherController: gather_item.gatherController

    RowLayout {
        anchors.fill: parent
        anchors.margins: 5

        GatherItem {
            id: gather_item
        }

        ColumnLayout {
            Layout.fillWidth: true
            Qaterial.GroupBox {
                id: box_serialport
                title: qsTr("Serial Port Configuration")
                inlineTitle: true

                Layout.fillWidth: true
                SerialPortConfigureView {
                    id: view_serialport
                    anchors.fill: parent
                } // SerialPortConfigureView
            }

            Qaterial.GroupBox {
                id: box_timeout
                title: qsTr("Timeout Configuration")
                inlineTitle: true
                Layout.fillWidth: true
                Column {
                    Qaterial.TextField {
                        title: qsTr("Gather Timeout Time")

                        text: "12000"
                    }
                    Qaterial.TextField {
                        title: qsTr("Sensor Timeout Time")
                        text: "12000"
                    }
                }
            }
            Qaterial.OutlineButton {
                id: btn_save
                text: qsTr("Save")
                Layout.alignment: Qt.AlignRight
                onClicked: {
                    if (!view_serialport.checkPortParam()) {
                        Qaterial.SnackbarManager.show({
                                                          text: "Serial Port configuration is error!"
                                                      })
                        return;
                    }
                    gather_item.portParam = view_serialport.portParam
                    Qaterial.SnackbarManager.show({
                                                      text: "Save Success!"
                                                  })
                }
            }
        }
    }
} // Rectangle
