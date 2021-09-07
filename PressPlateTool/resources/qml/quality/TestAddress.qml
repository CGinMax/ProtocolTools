import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Qaterial 1.0 as Qaterial

import PressPlateTools 1.0
Qaterial.GroupBox {
    id: _root

    property alias gatherController: _controller.gatherController
    property string nowPrefix: qsTr("Real time query address:")
    property string lastPrefix: qsTr("Last time query address:")
    property string timePrefix: qsTr("Update time:")
    property string noneSuffix: qsTr("None")
    property bool lastTimeSuccess: false
    RowLayout {
        anchors.fill: parent
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
                    timer_query_addr.stop()
                }
                else {
                    timer_addr_start.start()
                }

                isStart = !isStart;
            }
        }
        Qaterial.ToolSeparator {

        }

        Qaterial.Label {
            id: _nowAddrLabel
            property string value: _root.noneSuffix
            text: _root.nowPrefix + value
        }

        Qaterial.Label {
            id: _lastAddrLabel
            property string value: _root.noneSuffix
            text: _root.lastPrefix + value
        }
        Qaterial.Label {
            id: _timeLabel
            text: _root.timePrefix
            background: Rectangle {
                id: _timeBg
            }
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
                _lastAddrLabel.value = _nowAddrLabel.value;
            }

            if (result.success) {
                _nowAddrLabel.value = result.addr;
                _nowAddrLabel.color = "darkgreen";

                _timeLabel.text = _root.timePrefix + Qt.formatDateTime(new Date(), "yyyy-MM-dd hh:mm:ss");
                _timeLabel.color = "darkgreen";
            }
            else {
                _nowAddrLabel.value = _root.noneSuffix;
                _nowAddrLabel.color = "darkred";
                _timeLabel.text = _root.timePrefix;
                _timeLabel.color = "darkred";
            }

            lastTimeSuccess = result.success;
        }
    }
}
