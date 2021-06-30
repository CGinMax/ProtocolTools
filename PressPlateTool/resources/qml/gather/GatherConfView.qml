import QtQuick 2.12
import QtQuick.Controls 2.12

import Qaterial 1.0 as Qaterial

import PressPlateTools 1.0

Rectangle {
    id: _root

    property alias gather_count: list_gather.count

    ToolButtonBar {
        id: tool_btn_bar
        width: _root.width

        onAddClicked: function(count, portParam){
            controller_manager.addGatherConfig(count, portParam)
//            model_gather_configure.appendGather(count, portParam)
            list_gather.positionViewAtEnd()
        }
    } // ToolButtonBar

    ListView {
        id: list_gather
        anchors.top: tool_btn_bar.bottom
        anchors.topMargin: 10
        anchors.left: _root.left
        anchors.right: _root.right
        anchors.bottom: _root.bottom
        anchors.bottomMargin: 10
        spacing: 10
        cacheBuffer: list_gather.count * delegate_gather.height
        clip: true

        delegate: GatherItem {
            id: delegate_gather
            onQueryVersionClicked: {
                if (!controller_manager.isConnected(index)) {
                    Qaterial.SnackbarManager.show({
                        text: "Communication not open!Can not operate!"
                    })
                    return
                }

                controller_manager.queryVersion(index)
            }
            onConfigureAddrClicked: function(addr) {
                if (!controller_manager.isConnected(index)) {
                    Qaterial.SnackbarManager.show({
                        text: "Communication not open!Can not operate!"
                    })
                    return
                }

                controller_manager.configureAddress(index, addr)
            }
            onConfigureSensorCounterClicked: function(count) {
                Qaterial.SnackbarManager.show({
                    text: "Communication not open!Can not operate!"
                })
                if (!controller_manager.isConnected(index)) {
                    return
                }

                controller_manager.configureSensorCount(index, count)
            }
            onToggleCommunication: {
                if (!controller_manager.toggleCommunication(index)) {
                    console.log('index' + index)
                    console.log('start failed')

                } else {
                    isStarted = !isStarted
                }
            }

            onDeleteItem: {
                if (controller_manager.isConnected(index)) {
                    return
                }

                model_gather_configure.removeGather(index)
            }
        } // GatherItem

        model: GatherConfigureModel {
            id: model_gather_configure
        } // GatherConfigureModel
        ScrollBar.vertical: ScrollBar {
            width: 14
            active: true
            background: Item {}
            contentItem: Rectangle {
                radius: parent.width / 2
                color: 'grey'
            } // Rectangle

        } // ScrollBar


    } // ListView

    ControllerManager {

        id: controller_manager
        gatherModel: list_gather.model

    } // ControllerManager

//    Qaterial.SnackbarManager{
//        id: sb_manager
//        anchors.fill: parent
//        anchors.bottomMargin: 20
//    }

} // Rectangle
