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
    Q_PROPERTY(GatherData* gatherData READ gatherData WRITE setGatherData)
public:
    explicit SensorConfigureModel(QObject *parent = nullptr);
    ~SensorConfigureModel() override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void appendSensors(int count);
    Q_INVOKABLE void removeSensor(int index);
    Q_INVOKABLE void removeAll();


    Q_INVOKABLE void setGatherData(GatherData* data);
    Q_INVOKABLE GatherData* gatherData();
signals:

public slots:

private:
    GatherData* _gatherData;
};

#endif // SENSORCONFIGUREMODEL_H
