import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls 1.4 as Old
import QtQuick.Layouts 1.12

import PressPlateTools 1.0
import Qaterial 1.0 as Qaterial

Rectangle {
    id: _root

    property alias gatherData: model_sensor_configure.gatherData
    property alias gatherController: controller_sensor.gatherController



    ColumnLayout {

        anchors.fill: parent

        Qaterial.FlatButton {
            id: btn_add_one_sensor
            text: "Add one"
            onClicked: {
                model_sensor_configure.appendSensors(1)
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
                gatherData: null
            }

            delegate: SensorItem{
                id: delegate_sensor
                x: 10
                elevation: 0
                outlined: true
                width: listview_sensor.width - 20
                height: listview_sensor.delegateHeight

                list_model: model_sensor_configure
                controller: controller_sensor
            }


            SensorController {
                id: controller_sensor
                gatherController: null
            }

        }
    }

}
