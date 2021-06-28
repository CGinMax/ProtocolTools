#include "qmlexport.h"

#include "qmlserialporthelper.h"
#include "controller/controllermanager.h"
#include "model/gatherconfiguremodel.h"
#include <QQmlEngine>


void QmlExport::registerPressPlateType()
{

    const char* uri = "PressPlateTools";
    const int major_version = 1;
    const int minor_version = 0;
    qmlRegisterType<QmlSerialPortHelper>(uri, major_version, minor_version, "QmlSerialPortHelper");
    qmlRegisterType<GatherConfigureModel>(uri, major_version, minor_version, "GatherConfigureModel");
    qmlRegisterType<ControllerManager>(uri, major_version, minor_version, "ControllerManager");
}
