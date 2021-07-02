import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Qaterial 1.0 as Qaterial

import PressPlateTools 1.0
import "../page"

Rectangle {
    id: _root

    property alias gatherController: controller_sensor.gatherController

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
                onClicked: dialogLoader.sourceComponent = _queryVersionDialogComponent
                Component {
                    id: _queryVersionDialogComponent
                    Qaterial.ModalDialog {
                        standardButtons: Dialog.Cancel
                        contentItem: Rectangle {
                            ColumnLayout {

                                Text {
                                    Layout.alignment: Qt.AlignCenter
                                    id: text_info
                                    text: qsTr("Query Sensors Version...")
                                }
                                BusyIndicator {
                                    Layout.alignment: Qt.AlignCenter
                                    Layout.preferredHeight: 30
                                }
                            }
                        }
                        onClosed: dialogLoader.sourceComponent = undefined
                    }
                }
            }
            Qaterial.Button {
                id: btn_query_all_status
                text: qsTr("Automatic query sensor status")
                onClicked: {}
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

                list_model: model_sensor_configure
            }


            SensorController {
                id: controller_sensor
            }

        }
    }
}
