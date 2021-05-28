import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import Qaterial 1.0 as Qaterial

Rectangle {
    id: root


    Material.theme: Material.System
    Material.accent: Material.Blue

    Qaterial.TextField {
        id: search_field
        title: "search"
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            leftMargin: 30
            rightMargin: 20
        }
    }


    Qaterial.FlatButton {
        id: delete_btn
        text: "delete"
        anchors {
            top: parent.top
            bottom: search_field.bottom
            left: search_field.left
            right: parent.right
            leftMargin: 20
        }
    }

    Rectangle {
        id: expand_gather
        color: "blueviolet"
        anchors {
            top: search_field.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            topMargin: 10
        }
    }
}
