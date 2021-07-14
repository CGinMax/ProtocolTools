import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Qaterial 1.0 as Qaterial

Qaterial.ModalDialog {
    id: _root
    property string operText: ""
    property bool isFinish: false
    property bool isRun: visible
    property int curAddr: 0
    property color failedBg: "#FFBEC0"
    property color failedFg: "#E84B55"
    property color successBg: "#ACF5D2"
    property color successFg: "#1AB073"
    standardButtons: Dialog.Cancel
    contentItem: Rectangle {
        id: _content_item
        RowLayout {
            anchors.fill: parent
            spacing: 20
            ColumnLayout {
                Layout.alignment: Qt.AlignVCenter
                Layout.fillHeight: true
                Layout.fillWidth: true
                Text {
                    text:_root.operText + _root.curAddr
                    font.pixelSize: 16
                    font.bold: true
                }
                Loader {
                    id: loader_busy
                    Layout.alignment: Qt.AlignCenter
                    Layout.preferredHeight: 50

                }
            }
            ListView {
                id: listview_result
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredWidth: 200
                clip: true
                spacing: 5
                ScrollIndicator.vertical: ScrollIndicator { }
                delegate: Rectangle {
                    color: success ? _root.successBg : _root.failedBg
                    property color foreColor: success ? _root.successFg : _root.failedFg
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
            id: rect_finished
            visible: _root.isFinish
            anchors.fill: parent
            ColumnLayout {
                anchors.fill: parent
                Text {
                    id: text_finish
                    text: qsTr("Automatic operation finish!")
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
                    clip: true
                    spacing: 5
                    ScrollIndicator.vertical: ScrollIndicator { }
                    delegate: Rectangle {
                        color: success ? _root.successBg : _root.failedBg
                        property color foreColor: success ? _root.successFg : _root.failedFg
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
    onClosed: {
        drop();
    }
    onVisibleChanged: {
        if (_root.visible) {
            loader_busy.sourceComponent = Qt.createComponent("qrc:/Qaterial/BusyIndicator.qml");
        } else {
            loader_busy.sourceComponent.destroy();
            loader_busy.sourceComponent = null;
        }
    }

    function openDialog(text, addr) {
        _root.operText = text;
        _root.curAddr = addr;
        open();
    }

    function drop() {
        listmodel_result.clear();
        listmodel_finish.clear();
        isFinish = false;
    }

    function addModelData(success, name) {
        listmodel_result.append({success: success, sensor_name: name});
    }
    function finished() {
        isFinish = true;
        for (var i = 0; i < listview_result.count; i++) {
            if (!listmodel_result.get(i).success) {
                rect_finished.add_finish(listmodel_result.get(i).sensor_name);
            }
        }
    }
    function updateAddress(addr) {
        _root.curAddr = addr;
    }
}

