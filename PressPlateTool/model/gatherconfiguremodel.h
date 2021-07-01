#ifndef GATHERCONFIGUREMODEL_H
#define GATHERCONFIGUREMODEL_H

#include <QAbstractListModel>
#include <QSharedPointer>
#include "gatherdata.h"
class GatherConfigureModel : public QAbstractListModel
{
    Q_OBJECT
    enum RoleEnum {
        Name = Qt::UserRole,
        HardwareVersion,
        SoftwareVersion,
        ProductDesc,
        Address,
        SensorCount,
        Timeout,
    };

public:
    explicit GatherConfigureModel(QObject *parent = nullptr);
    ~GatherConfigureModel() override;

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void appendGathers(int count, const QVariantMap& map);
    Q_INVOKABLE void removeGather(int index);
    Q_INVOKABLE void removeAll();

    Q_INVOKABLE void updateVersion(int row, const QString& hardware, const QString& software, const QString& product);
    Q_INVOKABLE void updateAddress(int row, int addr);
    Q_INVOKABLE void updateSensorCount(int row, int count);

    Q_INVOKABLE QObject* portParam(int index);
signals:
public slots:
private:
    bool outOfRange(int index);

    QList<QSharedPointer<GatherData>> _gatherDataList;
};

#endif // GATHERCONFIGUREMODEL_H
