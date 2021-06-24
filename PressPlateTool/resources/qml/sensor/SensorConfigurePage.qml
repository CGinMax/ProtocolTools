import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qaterial 1.0 as Qaterial

Item {

    ListView {
        model: ListModel{
            ListElement{

            }
        }

        delegate: Qaterial.LabelHeadline1
    }
}
