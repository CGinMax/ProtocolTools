import QtQuick 2.12
import QtQuick.Controls 2.12

import Qaterial 1.0 as Qaterial

Qaterial.RoundButton {
    id: _root

    property url iconSource: undefined
    property double iconSize: 24

    signal clickStarted()

    Loader {
        id: loader_state
        sourceComponent: null
        anchors.fill: parent
    }

    Loader{
        id: loader_icon_inner
        asynchronous: true
        anchors.fill: parent
        sourceComponent: Qaterial.ColorIcon {
            id: icon_inner
            source: _root.iconSource
            iconSize: _root.iconSize

        }
    }

    onClicked: {
        createBusyLoading()
        emit: _root.clickStarted()
    }
    function createBusyLoading() {
        loader_icon_inner.item.visible = false
        loader_state.sourceComponent = Qt.createComponent("qrc:/Qaterial/BusyIndicator.qml");
    }

    function changeState(success) {
        if (loader_state.sourceComponent != null) {
            loader_state.sourceComponent.destroy()
            loader_state.sourceComponent = null
        }
        if (success) {
            loader_icon_inner.item.source = "image://faicon/check-circle"
            loader_icon_inner.item.color = "green"
        } else {
            loader_icon_inner.item.source = "image://faicon/times-circle"
            loader_icon_inner.item.color = "red"
        }
        loader_icon_inner.item.visible = true

        delay(2000, function(){
            loader_icon_inner.item.source = _root.iconSource
            loader_icon_inner.item.color = "black"
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
