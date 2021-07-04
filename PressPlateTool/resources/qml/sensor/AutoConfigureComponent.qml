import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Qaterial 1.0 as Qaterial

Qaterial.ModalDialog {
    id: _root
    property string text: ""
    standardButtons: Dialog.Cancel
    contentItem: Rectangle {
        id: _content_item
        property bool isFinish: false
        RowLayout {
            spacing: 40
            ColumnLayout {
                Layout.alignment: Qt.AlignVCenter
                Layout.fillHeight: true
                Layout.fillWidth: true
                Text {
                    Layout.alignment: Qt.AlignCenter
                    id: text_info
                    text: _root.text
                    font.pixelSize: 18
                }
                BusyIndicator {
                    Layout.alignment: Qt.AlignCenter
                    Layout.preferredHeight: 50
                }
            }
            ListView {
                id: listview_result
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredWidth: 200
                delegate: Rectangle {
//                    color: success ? "green" : "red"
                    property color foreColor: success ? "green" : "red"
                    border.color: "black"
                    width: listview_result.width
                    radius: 5
                    height: 30
                    Qaterial.ColorIcon {
                        source: success ? "image://faicon/check-circle" : "image://faicon/times-circle"
                        iconSize: 16
                        color: parent.foreColor
                        anchors.left: parent.left
                        anchors.leftMargin: 5
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Text {
                        text: sensor_name
                        color: parent.foreColor
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }

                }

                model: ListModel {
                    id: listmodel_result
                }
            }
        }

        Rectangle {
            visible: _content_item.isFinish
            anchors.fill: parent
            ColumnLayout {
                anchors.fill: parent
                Text {
                    id: text_finish
                    text: qsTr("Automatic query finish!")
                    font.pixelSize: 18
                    font.bold: true
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignCenter
                }
                ListView {
                    id: listview_finish
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.preferredWidth: parent.width
                    Layout.alignment: Qt.AlignCenter
                    delegate: Rectangle {
    //                    color: success ? "green" : "red"
                        property color foreColor: success ? "green" : "red"
                        border.color: "black"
                        width: listview_result.width
                        radius: 5
                        height: 30
                        Qaterial.ColorIcon {
                            source: "image://faicon/times-circle"
                            iconSize: 16
                            color: parent.foreColor
                            anchors.left: parent.left
                            anchors.leftMargin: 5
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Text {
                            text: sensor_name
                            color: parent.foreColor
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }

                    }
                    model: ListModel {
                        id: listmodel_finish
                    }
                }
            }
            function add_finish(name) {
                listmodel_finish.append({success: false, sensor_name: name})
            }
        }

    }
    onClosed: dialogLoader.sourceComponent = undefined
    function addModelData(success, name) {
        listmodel_result.append({success: success, sensor_name: name})
    }
}

