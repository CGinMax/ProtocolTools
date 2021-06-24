import QtQuick 2.12
import QtQuick.Window 2.12
//import QtQuick.Controls.Material 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls 1.4 as Old
import QtQuick.Layouts 1.12
import Qaterial 1.0 as Qaterial


Qaterial.ApplicationWindow {
    id: main_window
    visible: true
    width: 960
    height: 720

    title: qsTr("Press Plate Tool")

    Old.SplitView {
        anchors.fill: parent
        GatherConfView{
//            Layout.fillWidth: true
//            Layout.minimumWidth: 50
//            Layout.preferredWidth: 100
//            Layout.maximumWidth: 300
            width: 300
        }

        SensorConfView{

            width: 700
//            Layout.fillWidth: true
//            Layout.minimumWidth: 700
//            Layout.preferredWidth: 700
        }

        handleDelegate: Rectangle {
            width: 5
            color: Qaterial.Style.backgroundColor

        }
    }

    Component.onCompleted: {
        Qaterial.Style.theme = Qaterial.Style.Theme.Light
        main_window.x = (Screen.width - width) / 2
        main_window.y = (Screen.height - height) / 2
    }



}
