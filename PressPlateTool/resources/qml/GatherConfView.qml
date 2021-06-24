import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import Qaterial 1.0 as Qaterial

//import "gather"

Rectangle {
    id: root
    //    color: "#673AB7"

    Material.theme: Material.System
    Material.accent: Material.Blue

    Qaterial.Button{
        id: btn_delete_all
        text: "delete"
        anchors.right: root.right
        anchors.top: root.top
        anchors.topMargin: 3
    }

    ListView {
        id: list_gather
        anchors.top: btn_delete_all.bottom
        anchors.topMargin: 5
        anchors.left: root.left
        anchors.right: root.right
        anchors.bottom: root.bottom
        spacing: 10

        delegate: Qaterial.Card {
            x: 10
            width: parent.width - 20
            height: 200
            backgroundColor: bgColor
            Text {
                text: name
                anchors.centerIn: parent
            }
        }
        model: ListModel {
            ListElement{
                name: "1"
                bgColor: "red"
            }
            ListElement {
                name: "e"
                bgColor: "green"
            }
        }


    }
}
