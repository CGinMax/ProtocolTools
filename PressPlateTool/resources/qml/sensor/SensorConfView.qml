import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Qaterial 1.0 as Qaterial

import PressPlateTools 1.0

import "../data"

Rectangle {
    id: _root

    property var gatherController: null
    Loader {
        id: dialogLoader
        onLoaded: item.open()
    }
    ColumnLayout {

        anchors.fill: parent

        Row {
            Qaterial.Button {
                id: btn_add_one_sensor
                text: qsTr("Add one")
                onClicked: model_sensor_configure.appendSensors(1)
            }
            Qaterial.Button {
                id: btn_add_multi
                text: qsTr("Add Multiple")
                onClicked: dialogLoader.sourceComponent = _textFieldDialogComponent
                Component
                {
                    id: _textFieldDialogComponent
                    Qaterial.TextFieldDialog
                    {
                        id: _textFieldDialog
                        title: qsTr("Sensor Number Configuration")
                        textTitle: qsTr("Sensor Numbers")
                        text: "1"
                        validator: IntValidator{ bottom: 1}
                        inputMethodHints: Qt.ImhSensitiveData
                        errorText: length ? ("Don't write more than " + maximumLengthCount + " characters") : "Can't be empty"
                        maximumLengthCount: 16
                        trailingContent: Qaterial.TextFieldAlertIcon { visible: _textFieldDialog.errorState }
                        onAccepted: model_sensor_configure.appendSensors(parseInt(text))
                        onRejected: {}
                        onClosed: dialogLoader.sourceComponent = undefined
                    }
                }
            }
            Qaterial.Button {
                id: btn_query_all_version
                text: qsTr("Automatic query sensor version")
                enabled: listview_sensor.count !== 0
                onClicked: {
                    auto_query_dialog.text = qsTr("Query sensor version...");
                    auto_query_dialog.open();

                    _root.gatherController.querySensorVersion(0, model_sensor_configure.getAddr(0), ComConfig.sensorTimeout);
                }
            }
            Qaterial.Button {
                id: btn_query_all_status
                text: qsTr("Automatic query sensor status")
                enabled: listview_sensor.count !== 0
                onClicked: {
                    auto_query_dialog.text = qsTr("Query sensor status...");
                    auto_query_dialog.open();
                    _root.gatherController.querySensorState(0, model_sensor_configure.getAddr(0), ComConfig.sensorTimeout);
                }
            }
        }

        ListView {
            id: listview_sensor
            property int delegateHeight: 80
            clip: true
            cacheBuffer: count * delegateHeight

            Layout.fillWidth: true
            Layout.fillHeight: true
            model: SensorConfigureModel {
                id: model_sensor_configure
            }

            delegate: SensorItem{
                id: delegate_sensor
                x: 10
                elevation: 0
                outlined: true
                width: listview_sensor.width - 20
                height: listview_sensor.delegateHeight
                gatherController: _root.gatherController
                list_model: model_sensor_configure

            }
        }
    }
    AutoConfigureComponent{
        id: auto_query_dialog
        width: 500
        height: 300
    }
    Connections {
        target: gatherController
        onQuerySensorVersionCallback: function(success, index, hardware, software, product) {
            // stop by click cancel
            if (!auto_query_dialog.isRun) {
                return;
            }

            if (success) {
                model_sensor_configure.setVersion(index, hardware, software, product);
            }
            auto_query_dialog.addModelData(success, model_sensor_configure.getName(index));

            index++;
            if (index < listview_sensor.count) {
                _root.gatherController.querySensorVersion(index, model_sensor_configure.getAddr(index), ComConfig.sensorTimeout);
            } else {
                auto_query_dialog.finished();
            }
        }
        onQuerySensorStateCallback: function(success, index, curState, configuredState) {
            // stop by click cancel
            if (!auto_query_dialog.isRun) {
                return;
            }

            if (success) {
                model_sensor_configure.setState(index, curState, configuredState);
            }
            auto_query_dialog.addModelData(success, model_sensor_configure.getName(index));

            index++;
            if (index < listview_sensor.count) {
                _root.gatherController.querySensorState(index, model_sensor_configure.getAddr(index), ComConfig.sensorTimeout);
            } else {
                auto_query_dialog.finished();
            }
        }
    }
}
