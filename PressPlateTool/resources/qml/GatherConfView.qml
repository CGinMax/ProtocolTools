import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Rectangle {
    id: root


    Material.theme: Material.System
    Material.accent: Material.Blue

    Row {
        TextField {
            width: 40
        }
        Button {
            text: qsTr("delete")
        }
    }


}
