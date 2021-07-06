import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
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
    Qaterial.Page {
        anchors.fill: parent
        clip: true
        header: Qaterial.ClusturedTabBar {
            id: _tabBar
            currentIndex: _swipe_view.currentIndex
            onPrimary: true
            enabled: true

            model: ListModel {
                ListElement { text: qsTr("Gather Configure Page") }
                ListElement { text: qsTr("Sensor configure Page") }
                ListElement{ text: qsTr("Protocol")}
            }
        }
        Qaterial.SwipeView {
            id: _swipe_view
            anchors.fill: parent
            currentIndex: _tabBar.currentIndex
            interactive: true

            GatherConfView {
                id: view_gather_conf
            }
            SensorConfView {
                gatherController: view_gather_conf.gatherController
            }
            TextEdit {
                textFormat: TextEdit.RichText
            }

        } // SwipeView
    }
    Component.onCompleted: {
        Qaterial.Style.theme = Qaterial.Style.Theme.Light
        Qaterial.Style.primaryColorLight = Qaterial.Style.lightBlue
        Qaterial.Style.accentColorLight = Qaterial.Style.lightBlue
        main_window.x = (Screen.width - width) / 2
        main_window.y = (Screen.height - height) / 2
        main_window.visible = true
    }
}
