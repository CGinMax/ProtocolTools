import QtQuick 2.12
import QtQuick.Controls 2.12

import Qaterial 1.0 as Qaterial

Qaterial.RoundButton {
    id: _root

    property url iconSource: undefined
    property alias iconSize: icon_inner.iconSize

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
        createBusyLoading()
        emit: _root.clickStarted()
    }
    function createBusyLoading() {
        icon_inner.visible = false
        loader_state.sourceComponent = Qt.createComponent("qrc:/Qaterial/BusyIndicator.qml");
    }

    function changeState(success) {
        loader_state.sourceComponent.destroy()
        loader_state.sourceComponent = null
        if (success) {
            icon_inner.source = "image://faicon/check-circle"
            icon_inner.color = "green"
        } else {
            icon_inner.source = "image://faicon/times-circle"
            icon_inner.color = "red"
        }
        icon_inner.visible = true

        delay(2000, function(){
            icon_inner.source = _root.iconSource
            icon_inner.color = "black"
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
