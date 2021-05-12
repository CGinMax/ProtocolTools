#ifndef YBTABLEMODEL_H
#define YBTABLEMODEL_H

#include <QAbstractTableModel>
#include <QAbstractListModel>
#include <QList>
#include <QHash>

#include "../../common/ybsensordata.h"
class YBTableModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum eModelRoles{
        RoleId = Qt::UserRole + 1,
        RoleAddress,
        RoleVersion,
        RoleCurrentStatus,
        RoleConfigedStatus,
    };
    explicit YBTableModel(const QStringList& headers, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void append();
    void clearAllSensor();

signals:

public slots:

protected:
    QStringList m_headers;
    QHash<int, QByteArray> m_roleNames;
private:

    QList<YBSensorData> m_sensorDataList;
};

#endif // YBTABLEMODEL_H
