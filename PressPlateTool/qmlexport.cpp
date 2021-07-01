#include "qmlexport.h"

#include "qmlserialporthelper.h"
#include "controller/gathercontroller.h"
#include "controller/sensorcontroller.h"
#include "model/gatherconfiguremodel.h"
#include "model/sensorconfiguremodel.h"
#include <QQmlEngine>


void QmlExport::registerPressPlateType()
{

    const char* uri = "PressPlateTools";
    const int major_version = 1;
    const int minor_version = 0;

    qmlRegisterType<QmlSerialPortHelper>(uri, major_version, minor_version, "QmlSerialPortHelper");
    qmlRegisterType<GatherController>(uri, major_version, minor_version, "GatherController");
    qmlRegisterType<SensorController>(uri, major_version, minor_version, "SensorController");
    qmlRegisterType<GatherConfigureModel>(uri, major_version, minor_version, "GatherConfigureModel");
    qmlRegisterType<SensorConfigureModel>(uri, major_version, minor_version, "SensorConfigureModel");

}
