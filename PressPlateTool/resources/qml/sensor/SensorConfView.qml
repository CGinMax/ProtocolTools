import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import Qaterial 1.0 as Qaterial

import "../page"

Rectangle {
    id: _root

    Text {
        id: text_gather_name
        width: 50
        height: 30
        text: qsTr("Sensor")
        font.pixelSize: 24
        anchors.left: _root.left
        anchors.leftMargin: 5
        anchors.top: _root.top
        anchors.topMargin: 5
    }

    Qaterial.Page {
        anchors.top: text_gather_name.bottom
        anchors.bottom: _root.bottom
        anchors.left: _root.left
        anchors.right: _root.right
        anchors.topMargin: 5
        clip: true
        header: Qaterial.ClusturedTabBar {
            id: _tabBar
            currentIndex: _swipe_view.currentIndex
            onPrimary: true
            enabled: true

            model: ListModel
            {
                ListElement { text: qsTr("Sensor") }
                ListElement { text: qsTr("Configure") }
            }
        }
        Qaterial.SwipeView
        {
            id: _swipe_view
            anchors.fill: parent
            currentIndex: _tabBar.currentIndex
            interactive: true
            SensorConfigurePage {
                id: page_sensor_configure
            } // SensorConfigurePage

            ProjectConfigurePage {
                id: _page_project_conf
                width: _swipe_view.width
                height: _swipe_view.height
            } // ProjectConfigurePage

        } // SwipeView
    }

    function setController(gatherController, gatherData) {
        page_sensor_configure.gatherController = gatherController
        page_sensor_configure.gatherData = gatherData
    }

}
