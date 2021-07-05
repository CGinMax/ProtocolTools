
pragma Singleton

import QtQuick 2.0

QtObject {
    property string devName: ""
    property int baudrate: 9600
    property int gatherTimeout: 10000
    property int sensorTimeout: 10000
}
