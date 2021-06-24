import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qaterial 1.0 as Qaterial


Qaterial.ApplicationWindow {
    id: main_window
    visible: true
    width: 960
    height: 720

    title: qsTr("Press Plate Tool")

    RowLayout {
        spacing: 2
        anchors.fill: parent
        GatherConfView {
            Layout.fillWidth: true
            Layout.minimumWidth: 50
            Layout.preferredWidth: 100
            Layout.maximumWidth: 300
            Layout.minimumHeight: parent.height
        }
//        Qaterial.S
        SensorConfView {
            Layout.fillWidth: true
            Layout.minimumWidth: 100
            Layout.preferredWidth: 200
            Layout.preferredHeight: parent.height
        }

    }

    Component.onCompleted: {
        Qaterial.Style.theme = Qaterial.Style.Theme.Light
        main_window.x = (Screen.width - width) / 2
        main_window.y = (Screen.height - height) / 2
    }



}
