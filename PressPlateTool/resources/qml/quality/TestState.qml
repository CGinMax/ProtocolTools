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
    property string noneSuffix: qsTr("None")
    property color bgColor: ThemeConfig.failedBgColor
    property color textColor: ThemeConfig.failedFgColor
    property bool lastTimeSuccess: false

    title: qsTr("Test State")
    inlineTitle: true

    ColumnLayout {
        anchors.fill: parent
        spacing: 30

        RowLayout {
            spacing: 20
            Layout.alignment: Qt.AlignTop
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
                width: 13
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
        Row {
            spacing: 20
//            Layout.alignment: Qt.AlignTop
            RealtimeLabel {
                id: _nowTimeLabel
                prefixText: qsTr("Update time:")
                suffixText: _root.noneSuffix
                bgColor: _root.bgColor
                textColor: _root.textColor
            }

            RealtimeLabel {
                id: _lastTimeLabel
                prefixText: qsTr("Last update time:")
                suffixText: _root.noneSuffix
                bgColor: ThemeConfig.successBgColor
                textColor: ThemeConfig.successFgColor
            }
        }
        Column {
            spacing: 20
//            Layout.alignment: Qt.AlignTop
            RealtimeLabel {
                id: _stateLabel
                prefixText: qsTr("Real time query state:")
                suffixText: _root.noneSuffix
                bgColor: _root.bgColor
                textColor: _root.textColor
            }

            RealtimeLabel {
                id: _versionLabel
                prefixText: qsTr("Real time query version:")
                suffixText: _root.noneSuffix
                bgColor: _root.bgColor
                textColor: _root.textColor
            }
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
                _versionLabel.suffixText = content;
            }
            else {
                _versionLabel.suffixText = _root.noneSuffix;
            }

            updateTime(result.success);
            updateColor(_versionLabel, result.success);
        }
        onQueryStateCallback: function(result/*success, curState, confState*/) {
            if (result.success) {
                var content = qsTr("current status:") + result.curState + ", ";
                content += qsTr("configure status:") + result.confState;
                _stateLabel.suffixText = content;
            }
            else {
                _stateLabel.suffixText = _root.noneSuffix;
            }

            updateTime(result.success);
            updateColor(_stateLabel, result.success);
        }
        onConfigureStateCallback: function(result) {
            if (result.success) {
            }
            loader_btn_configure_status.changeState(result.success)
        }
    }

    function updateTime(success) {
        if (_root.lastTimeSuccess) {
            _lastTimeLabel.suffixText = _nowTimeLabel.suffixText;
        }

        _nowTimeLabel.suffixText = success ? Qt.formatDateTime(new Date(), "yyyy-MM-dd hh:mm:ss") : "";
        updateColor(_nowTimeLabel, success);
        _root.lastTimeSuccess = succes;
    }

    function updateColor(label, success) {
        label.bgColor = success ? ThemeConfig.successBgColor : ThemeConfig.failedBgColor;
        label.textColor = success ? ThemeConfig.successFgColor : ThemeConfig.failedFgColor;
    }

}
