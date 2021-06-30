import QtQuick 2.12
import QtQuick.Controls 2.12

import Qaterial 1.0 as Qaterial

Qaterial.RoundButton {
    id: _root

    property url iconSource: undefined
    property alias iconSize: icon_inner.iconSize
    property int actionState: 0

    signal clickStarted()

    Loader {
        id: loader_state
        sourceComponent: null
        anchors.fill: parent
    }

    Qaterial.ColorIcon {
        id: icon_inner
        source: _root.iconSource
        anchors.fill: parent

    }


    onClicked: {
        // TODO
        if (actionState == 1) {
            actionState = 0

        } else {
            actionState = 1
            emit: _root.clickStarted()
        }

    }

    onActionStateChanged: {
        if (actionState == 0) {
            icon_inner.source = _root.iconSource
            icon_inner.visible = true
        } else if (actionState == 1) {
            createBusyLoading()
        } else {
            changeState(actionState == 2)
            console.log("aaa")
        }
    }

    function createBusyLoading() {
        icon_inner.visible = false
        loader_state.sourceComponent = Qt.createComponent("qrc:/Qaterial/BusyIndicator.qml");

    }

    function changeState(success) {

        if (success) {
            icon_inner.icon.source = "image://faicon/check-circle"
            icon_inner.icon.color = "green"
        } else {
            icon_inner.icon.source = "image://faicon/times-circle"
            icon_inner.icon.color = "red"
        }
        icon_inner.visible = true

        delay(2000, function(){
            icon_inner.source = _root.iconSource
        })
    }
    function new_timer() {
        return Qt.createQmlObject("import QtQuick 2.12; Timer{}", _root)
    }
    function delay(interval, callback) {
        var timer = new_timer()
        timer.interval = interval
        timer.repeat = false
        timer.triggered.connect(callback)
        timer.start()
    }
}
