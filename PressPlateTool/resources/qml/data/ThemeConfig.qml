pragma Singleton
import QtQuick 2.12

QtObject {
    property color openBgColor: "#FFBEC0"
    property color openFgColor: "#E84B55"
    property color closeBgColor: "#ACF5D2"
    property color closeFgColor: "#1AB073"
    property color unknowBgColor: "#F6F6F6"
    property color unknowFgColor: "#9E9E9E"
    property color exceptionBgColor: "#EFD360"
    property color exceptionFgColor: "#FFF6D7"

    property color successBgColor: closeBgColor
    property color successFgColor: closeFgColor
    property color failedBgColor: openBgColor
    property color failedFgColor: openFgColor
}
