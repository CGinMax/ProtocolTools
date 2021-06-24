import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import Qaterial 1.0 as Qaterial

import "./gather"

Rectangle {
    id: root
    //    color: "#673AB7"

    ToolButtonBar {
        id: tool_btn_bar
        width: root.width
    }

    ListView {
        id: list_gather
        anchors.top: tool_btn_bar.bottom
        anchors.topMargin: 10
        anchors.left: root.left
        anchors.right: root.right
        anchors.bottom: root.bottom
        anchors.bottomMargin: 10
        spacing: 10
        clip: true

        delegate: Qaterial.Card {
            x: 10
            width: parent.width - 20
            height: 200
            elevation: 8.0
            elevationOnHovered: true
            outlined: true
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
            ListElement {
                name: "e"
                bgColor: "green"
            }
            ListElement {
                name: "e"
                bgColor: "green"
            }
            ListElement {
                name: "e"
                bgColor: "green"
            }
            ListElement {
                name: "e"
                bgColor: "green"
            }

        }
        ScrollBar.vertical: ScrollBar {
            width: 14
            active: true
            background: Item {
            }
            contentItem: Rectangle {
                radius: parent.width / 2
                color: 'grey'
            }

        }
    }
}
