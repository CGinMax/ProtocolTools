#ifndef QMLSERIALPORTHELPER_H
#define QMLSERIALPORTHELPER_H

#include <QObject>
#include "communication_global.h"

class COMMUNICATIONSHARED_EXPORT QmlSerialPortHelper : public QObject
{
    Q_OBJECT
public:
    explicit QmlSerialPortHelper(QObject *parent = nullptr);
    ~QmlSerialPortHelper() override;

    Q_INVOKABLE QList<QString> availablePorts();

    Q_INVOKABLE QList<int> standardBaudRates();
signals:

public slots:

};

#endif // QMLSERIALPORTHELPER_H
