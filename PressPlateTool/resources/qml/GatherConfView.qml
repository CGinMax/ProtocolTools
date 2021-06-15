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

    Qaterial.ScrollView {
        id: sv
        anchors.fill: parent
        ColumnLayout {
            id: cl
            anchors.fill: parent
            Qaterial.Card {
                Layout.fillWidth: true
                Layout.minimumWidth: 50
                Layout.preferredWidth: 100
                Layout.maximumWidth: 300
                Layout.minimumHeight: 100
                background: Qaterial.CardBackground {
                    color: "green"
                }
                elevation: 10
                width: parent.width
            }
            Qaterial.Card{

                Layout.fillWidth: true
                Layout.minimumWidth: 50
                Layout.preferredWidth: 100
                Layout.maximumWidth: 300
                Layout.minimumHeight: 100
                background: Qaterial.CardBackground {
                    color: "red"
                }

                width: parent.width
            }
            Qaterial.Card {
                Layout.fillWidth: true
                Layout.minimumWidth: 50
                Layout.preferredWidth: 100
                Layout.maximumWidth: 300
                Layout.minimumHeight: 100

                width: parent.width
            }
            Qaterial.Card {
                Layout.fillWidth: true
                Layout.minimumWidth: 50
                Layout.preferredWidth: 100
                Layout.maximumWidth: 300
                Layout.minimumHeight: 100
                width: parent.width
                elevation: 10
            }
            Qaterial.Card {
                Layout.fillWidth: true
                Layout.minimumWidth: 50
                Layout.preferredWidth: 100
                Layout.maximumWidth: 300
                Layout.minimumHeight: 100
                width: parent.width
                elevation: 10
            }
        }


    }
}
