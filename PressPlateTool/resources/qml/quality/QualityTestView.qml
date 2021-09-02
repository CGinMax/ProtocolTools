import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls 1.4 as Old

import Qaterial 1.0 as Qaterial

import "../components"
import "../data"

import PressPlateTools 1.0
Rectangle {
    property alias gatherController: _controller.gatherController
    id: _root
    ColumnLayout {
        anchors.fill: parent
        Row {
            Layout.alignment: Qt.AlignCenter
            spacing: 20
            Qaterial.TextField {
                id: text_address
                title: qsTr("Sensor Address")
                text: "1"
                validator: IntValidator{ bottom: 0 }
            }

            Qaterial.Button {
                id: btn_start
                property bool isStart: false
                text: isStart ? qsTr("Stop") : qsTr("Start")
                onClicked: {
                    if (!_controller.isConnected()) {
                        gatherController.alertNotOpen();
                        return ;
                    }
                    if (isStart) {
                        timer_query_status.stop()
                        timer_query_version.stop()
                    }
                    else {
                        timer_status_start.start()
                        timer_version_start.start()
                    }

                    isStart = !isStart;
                }
            }

            Qaterial.ComboBox {
                id: cbb_status
                borderColor: "gray"
                model: [qsTr("Open"), qsTr("Close"), qsTr("Unconfigured")]
            }

            LoadingButton {
                id: loader_btn_configure_status
                iconSource: "image://faicon/arrow-alt-circle-left"
                iconSize: 18
                onClickStarted: {
                    _controller.configureSensorStatus(parseInt(text_address.text),
                                                      cbb_status.currentIndex !== 2 ?
                                                          cbb_status.currentIndex : 0xFF,
                                                      ComConfig.sensorTimeout);
                }
                ToolTip{
                    visible: parent.hovered
                    text: qsTr("Configure sensor state")
                }
            }
        }

        Old.TextArea {
            id: edit_protocol
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.margins: 5

            textFormat: TextEdit.RichText
        }
    }
    Timer {
        id: timer_version_start
        interval: 400
        repeat: false
        onTriggered: timer_query_version.start()
    }

    Timer {
        id: timer_status_start
        interval: 800
        repeat: false
        onTriggered: timer_query_status.start()
    }

    Timer {
        id: timer_query_version
        interval: 2000
        repeat: true
        onTriggered: {
            _controller.querySensorVersion(parseInt(text_address.text), 2000)
        }
    }
    Timer {
        id: timer_query_status
        interval: 2000
        repeat: true
        onTriggered: {
            _controller.querySensorStatus(parseInt(text_address.text), 2000)
        }
    }
    SensorController {
        id: _controller
        onQueryVersionCallback: function(result/* success, hardware, software, product*/) {
            if (result.success) {
                var content = qsTr("Hardware version: ") + result.hardware + ", ";
                content += qsTr("Software version: ") + result.software + ", ";
                content += qsTr("Product: ") + result.product;
                addSuccessMsg(qsTr("Query version success"), content)
            }
        }
        onQueryStateCallback: function(result/*success, curState, confState*/) {
            if (result.success) {
                var content = qsTr("current status:") +result.curState + ", " + qsTr("configure status:") + result.confState
                addSuccessMsg(qsTr("Query status success"), content)
           }
        }
        onConfigureStateCallback: function(result) {
            if (result.success) {
                addSuccessMsg(qsTr("Configure status success"), "")
            }
            loader_btn_configure_status.changeState(result.success)
        }
    }


    function addSuccessMsg(title, content) {
        var now = new Date();
        edit_protocol.append(Qt.formatDateTime(now, "yyyy-MM-dd hh:mm:ss") + ":" + title)
        edit_protocol.append(content)
        edit_protocol.append("")
    }
}
