import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import PressPlateTools 1.0
import Qaterial 1.0 as Qaterial

import "../components"

Rectangle {
    id: _root

    property alias gatherController: gather_item.gatherController

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        ComConfigureView {
            id: view_com_configure
            isStarted: gather_item.isStarted
            Layout.fillWidth: true
            Layout.preferredHeight: 150
            onToggleCommunication: function(portParam) {
                gather_item.toggleCommunication(portParam);
            }
        }

        GatherItem {
            id: gather_item
        }
    }
} // Rectangle
