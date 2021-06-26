#ifndef GATHERCONFIGUREMODEL_H
#define GATHERCONFIGUREMODEL_H

#include <QAbstractListModel>
#include "gatherdata.h"
class GatherConfigureModel : public QAbstractListModel
{
    Q_OBJECT
    enum RoleEnum {
        Name = Qt::UserRole,
        HardwareVersion,
        SoftwareVersion,
        Address,
    };

public:
    explicit GatherConfigureModel(QObject *parent = nullptr);
    ~GatherConfigureModel() override = default;


    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
signals:

public slots:
    QList<GatherData*> m_gatherDataList;
};

#endif // GATHERCONFIGUREMODEL_H
