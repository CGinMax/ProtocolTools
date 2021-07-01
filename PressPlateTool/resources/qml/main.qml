import QtQuick 2.12
import QtQuick.Window 2.12
//import QtQuick.Controls.Material 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls 1.4 as Old
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

//    Qaterial.TreeView {
//        idth: 300
//        height: parent ? Math.min(contentHeight, parent.height) : contentHeight

//        property QtObject selectedElement


//        itemDelegate: Qaterial.ItemDelegate
//        {
//            id: control

//            property QtObject model
//            property int depth
//            property int index

//            height: 24
//            leftPadding: depth * 20

//            contentItem: RowLayout
//            {
//                Qaterial.ColorIcon
//                {
//                    source: Qaterial.Icons.chevronRight
//                    color: Qaterial.Style.primaryTextColor()
//                    visible: control.model && control.model.children && control.model.children.count
//                    Binding on rotation
//                    {
//                        when: control.model && control.model.expanded
//                        value: 90
//                    }
//                    Behavior on rotation { NumberAnimation { duration: 200;easing.type: Easing.OutQuart } }
//                }
//                Qaterial.Label
//                {
//                    Layout.fillWidth: true
//                    text: control.model ? control.model.text : ""
//                    elide: Text.ElideRight
//                    verticalAlignment: Text.AlignVCenter
//                    Binding on color
//                    {
//                        when: model === root.selectedElement
//                        value: Qaterial.Style.accentColor
//                    }
//                }
//            }

//            onClicked: function()
//            {
//                if(model.children.count !== 0)
//                    model.expanded = !model.expanded
//                else
//                    root.selectedElement = model
//            }
//        }
//    }

    Old.SplitView {
        anchors.fill: parent
        GatherConfView{
            id: view_gather_config

            property bool isCollapse: false

            width: 300

            function collapse() {
                width = isCollapse ? 300 : 0
                isCollapse = !isCollapse
            }
            onItemChanged: function(gatherController, gatherData) {
                view_sensor_config.setController(gatherController, gatherData)
            }

            //            Behavior on width {
            //                NumberAnimation {
            //                    duration: 200
            //                }
            //            }
        }

        StackLayout {
            id: stacklayout_sensor
            currentIndex: view_gather_config.gather_count == 0 ? 0 : 1
            Rectangle {
            }

            SensorConfView{
                id: view_sensor_config

            }
        }



        handleDelegate: SplitHandle{}

        Component.onCompleted: {
            Qaterial.Style.theme = Qaterial.Style.Theme.Light
            main_window.x = (Screen.width - width) / 2
            main_window.y = (Screen.height - height) / 2
            main_window.visible = true
        }

    }
}
