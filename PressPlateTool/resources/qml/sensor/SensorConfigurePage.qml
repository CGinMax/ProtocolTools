import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls 1.4 as Old
import QtQuick.Layouts 1.12

import Qaterial 1.0 as Qaterial

Rectangle {
    id: _root

    Old.SplitView {
        id: _sv_vertical
        orientation: Qt.Vertical
        anchors.fill: parent

        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true


            ListView {
                model: ListModel{
                    ListElement{
                        titleName: "sensor1"
                        hardwareVersion: 1
                        softwareVersion: 0
                    }

                }

                delegate: Rectangle {
                    color: "blue"
                    border.color: "grey"
                    ColumnLayout {
    //                    anchors.fill: parent
                        Layout.alignment: Qt.AlignCenter
                        Qaterial.Label{
                            text: titleName
                        }
                        Qaterial.Label {
                            text: hardwareVersion
                        }
                        Qaterial.Label {
                            text: softwareVersion
                        }
                    }


                }
            }
        }



        Qaterial.TextArea {
            Layout.fillWidth: true
            Layout.fillHeight: true

            backgroundBorderHeight: 10
        }

        handleDelegate: Rectangle {
            width: 5
//            color: Qaterial.Style.backgroundColor
            color: "black"

        }
    }




}
