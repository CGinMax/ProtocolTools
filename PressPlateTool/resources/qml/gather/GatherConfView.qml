import QtQuick 2.12
import QtQuick.Controls 2.12

import PressPlateTools 1.0
import Qaterial 1.0 as Qaterial

Rectangle {
    id: _root

    property alias gather_count: listview_gather.count

    ToolButtonBar {
        id: tool_btn_bar
        width: _root.width

        onAddClicked: function(count, portParam){
            model_gather_configure.appendGathers(count, portParam)
            listview_gather.positionViewAtEnd()
        }
        onDeleteAll: {
            model_gather_configure.removeAll();
        }
    } // ToolButtonBar

    ListView {
        id: listview_gather

        property int delegateHeight: 200

        spacing: 10
        clip: true
        cacheBuffer: listview_gather.count * delegateHeight
        anchors.top: tool_btn_bar.bottom
        anchors.topMargin: 10
        anchors.left: _root.left
        anchors.right: _root.right
        anchors.bottom: _root.bottom
        anchors.bottomMargin: 10

        delegate: GatherItem {
            id: delegate_gather
            width: listview_gather.width - 40
            height: listview_gather.delegateHeight
            list_model: model_gather_configure
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

} // Rectangle
