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
    };

public:
    explicit GatherConfigureModel(QObject *parent = nullptr);
    ~GatherConfigureModel() override;

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void appendGatherList(const QList<QSharedPointer<GatherData>>& dataList);
    Q_INVOKABLE void removeGather(int index);

    QList<QSharedPointer<GatherData>> gatherDataList() const;
signals:
public slots:
private:
    QList<QSharedPointer<GatherData>> _gatherDataList;
};

#endif // GATHERCONFIGUREMODEL_H
