import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Qaterial 1.0 as Qaterial
import PressPlateTools 1.0
import "../components"
import "../data"
Qaterial.GroupBox {
    id: _root

    property alias gatherController: _controller.gatherController
    property string noneSuffix: qsTr("None")
    property bool lastTimeSuccess: false
    property color bgColor: ThemeConfig.failedBgColor
    property color textColor: ThemeConfig.failedFgColor

    title: qsTr("Test Address")
    inlineTitle: true
    RowLayout {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: parent / 3
        Qaterial.Button {
            id: btn_start
            property bool isStart: false
            Layout.alignment: Qt.AlignVCenter
            text: isStart ? qsTr("Stop") : qsTr("Start")
            onClicked: {
                if (!_controller.isConnected()) {
                    gatherController.alertNotOpen();
                    return ;
                }
                if (isStart) {
                    timer_query_addr.stop()
                }
                else {
                    timer_addr_start.start()
                }

                isStart = !isStart;
            }
        }
        Qaterial.ToolSeparator {
            Layout.alignment: Qt.AlignVCenter
        }

        RealtimeLabel {
            Layout.alignment: Qt.AlignVCenter
            id: _nowAddrLabel
            prefixText: qsTr("Real time query address:")
            suffixText: _root.noneSuffix
            bgColor: _root.bgColor
            textColor: _root.textColor
        }


        RealtimeLabel {
            Layout.alignment: Qt.AlignVCenter
            id: _lastAddrLabel
            prefixText: qsTr("Last time query address:")
            suffixText: _root.noneSuffix
            bgColor: _root.bgColor
            textColor: _root.textColor
        }

        RealtimeLabel {
            Layout.alignment: Qt.AlignVCenter
            id: _timeLabel
            prefixText: qsTr("Update time:")
            suffixText: _root.noneSuffix
            bgColor: ThemeConfig.successBgColor
            textColor: ThemeConfig.successFgColor
        }
    }

    Timer {
        id: timer_addr_start
        interval: 400
        repeat: false
        onTriggered: timer_query_addr.start()
    }

    Timer {
        id: timer_query_addr
        interval: 2000
        repeat: true
        onTriggered: {
            _controller.querySensorAddr(2000);
        }
    }

    SensorController {
        id: _controller
        onQueryAddrCallback: function(result) {
            if (_root.lastTimeSuccess) {
                _lastAddrLabel.suffixText = _nowAddrLabel.suffixText;
            }

            if (result.success) {
                _nowAddrLabel.suffixText = result.addr;

                _timeLabel.suffixText = Qt.formatDateTime(new Date(), "yyyy-MM-dd hh:mm:ss");
            }
            else {
                _timeLabel.suffixText = "";
            }

            _root.bgColor = result.success ? ThemeConfig.successBgColor : ThemeConfig.failedBgColor;
            _root.textColor = result.success ? ThemeConfig.successFgColor : ThemeConfig.failedFgColor;
            lastTimeSuccess = result.success;
        }
    }
}
