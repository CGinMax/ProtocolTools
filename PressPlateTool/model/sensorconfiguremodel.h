#ifndef SENSORCONFIGUREMODEL_H
#define SENSORCONFIGUREMODEL_H

#include <QAbstractListModel>
#include <QSharedPointer>
#include "gatherdata.h"
class SensorConfigureModel : public QAbstractListModel
{
    Q_OBJECT
    enum RoleEnum {
        Name = Qt::UserRole,
        HardwareVersion,
        SoftwareVersion,
        ProductDesc,
        Address,
        CurrentStatus,
        ConfiguredStatus,
        Timeout,
    };
public:
    explicit SensorConfigureModel(QObject *parent = nullptr);
    ~SensorConfigureModel() override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void appendSensors(int count);
    Q_INVOKABLE void removeSensor(int index);
    Q_INVOKABLE void removeAll();

signals:

public slots:

private:
    QList<QSharedPointer<YBSensorData>> _ybSensorDataList;
};

#endif // SENSORCONFIGUREMODEL_H
