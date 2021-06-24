import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12
import Qaterial 1.0 as Qaterial

Rectangle {
    id: _root
//    color: "#4CAF50"
    Text {
        id: text_gather_name
        width: 50
        height: 30
        text: qsTr("text")
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
            currentIndex: _swipeView.currentIndex
            onPrimary: true
            enabled: true

            model: ListModel
            {
                ListElement { text: "Sensor" }
                ListElement { text: "Configure" }
            }
        }
        Qaterial.SwipeView
        {
            id: _swipeView
            anchors.fill: parent
            currentIndex: _tabBar.currentIndex
            interactive: true
            Item
            {
                width: _swipeView.width
                height: _swipeView.height

                Text
                {
                    anchors.centerIn: parent
                    text: "Landscape View"
                    color: "#FF2196F3"
                } // Label
            } // Item

            Item
            {
                width: _swipeView.width
                height: _swipeView.height

                Text
                {
                    anchors.centerIn: parent
                    text: "City View"
                    color: "#FF00BCD4"
                } // Label
            } // Item

        } // SwipeView
    }

}
