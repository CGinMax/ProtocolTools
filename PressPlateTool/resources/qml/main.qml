import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls 2.12
import Qaterial 1.0 as Qaterial

Qaterial.ApplicationWindow {
    id: main_window
    visible: true
    width: 960
    height: 720
    x: (Screen.width - width) / 2
    y: (Screen.height - height) / 2

    title: qsTr("Press Plate Tool")

//    Material.theme: Material.System
//    Material.accent: Material.Blue

//    Row {
//        GatherConfView {

//        }

//        ToolSeparator{}
//        SensorConfView {

//        }
//    }




}
