import QtQuick 2.12
import QtQuick.Window 2.12
//import QtQuick.Controls.Material 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls 1.4 as Old
import QtQuick.Layouts 1.12
import Qaterial 1.0 as Qaterial

import "gather"
import "sensor"
import "components"

Qaterial.ApplicationWindow {
    id: main_window
    width: 960
    height: 720

    title: qsTr("Press Plate Tool")

    Old.SplitView {
        anchors.fill: parent
        GatherConfView{
            id: view_gather_config

            property bool isCollapse: false

            width: 300

            function collapse() {
                width = isCollapse ? 300 : 0
                isCollapse = !isCollapse
            }

//            Behavior on width {
//                NumberAnimation {
//                    duration: 200
//                }
//            }
        }

        StackLayout {
            id: stacklayout_sensor
            currentIndex: view_gather_config.gather_count == 0 ? 0 : 1
            Rectangle {
            }

            SensorConfView{
            }
        }



        handleDelegate: SplitHandle{}

        Component.onCompleted: {
            Qaterial.Style.theme = Qaterial.Style.Theme.Light
            main_window.x = (Screen.width - width) / 2
            main_window.y = (Screen.height - height) / 2
            main_window.visible = true
        }



    }
}
