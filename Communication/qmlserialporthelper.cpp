#include "qmlserialporthelper.h"
#include <QSerialPortInfo>

QmlSerialPortHelper::QmlSerialPortHelper(QObject *parent) : QObject(parent)
{

}

QmlSerialPortHelper::~QmlSerialPortHelper()
{

}

QList<QString> QmlSerialPortHelper::availablePorts()
{
    auto serialports = QSerialPortInfo::availablePorts();
    QList<QString> result;
    for (const auto& serialport : serialports) {
        result.append(serialport.portName());
    }

    return result;
}

QList<int> QmlSerialPortHelper::standardBaudRates()
{
    return QSerialPortInfo::standardBaudRates();
}
