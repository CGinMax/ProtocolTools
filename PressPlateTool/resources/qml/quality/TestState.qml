import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qaterial 1.0 as Qaterial

import "../components"
import "../data"
import PressPlateTools 1.0
Qaterial.GroupBox {
    id: _root
    property alias gatherController: _controller.gatherController
    property string nowTimePrefix: qsTr("Update time:")
    property string lastTimePrefix: qsTr("Last update time:")
    property string noneSuffix: qsTr("None")
    property bool lastTimeSuccess: false
    title: qsTr("Test State")

    ColumnLayout {
        anchors.fill: parent

        Row {
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

            Qaterial.ToggleSeparator {

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
                                                      cbb_status.currentIndex !== 2
                                                      ? cbb_status.currentIndex : 0xFF,
                                                      ComConfig.sensorTimeout);
                }
                ToolTip{
                    visible: parent.hovered
                    text: qsTr("Configure sensor state")
                }
            }
        }
        Qaterial.Label {
            id: _nowTimeLabel
            text: _root.nowTimePrefix
            property string value: _root.noneSuffix
            background: Rectangle {
                id: _nowTimeBg
            }
        }
        Qaterial.Label {
            id: _lastTimeLabel
            text: _root.lastTimePrefix
            property string value: _root.noneSuffix
            background: Rectangle {
                id: _lastTimeBg
            }
        }

        Qaterial.Label {
            id: _versionLabel
            text: _root.noneSuffix
        }
        Qaterial.Label {
            id: _stateLabel
            text: _root.noneSuffix
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
                _versionLabel.text = content;
            }
            else {
                _versionLabel.text = _root.noneSuffix;
            }

            updateTime(result.success);
        }
        onQueryStateCallback: function(result/*success, curState, confState*/) {
            if (result.success) {
                var content = qsTr("current status:") +result.curState + ", " + qsTr("configure status:") + result.confState
                _stateLabel.text = content;
            }
            else {
                _versionLabel.text = _root.noneSuffix;
            }

            updateTime(result.success);
        }
        onConfigureStateCallback: function(result) {
            if (result.success) {
            }
            loader_btn_configure_status.changeState(result.success)
        }
    }

    function updateTime(success) {
        if (_root.lastTimeSuccess) {
            _lastTimeLabel.value = _nowTimeLabel.value;
        }

        if(success) {
            _nowTimeLabel.value = Qt.formatDateTime(new Date(), "yyyy-MM-dd hh:mm:ss")
        }
        else {
            _nowTimeLabel.value = _root.noneSuffix;
        }
    }

}
