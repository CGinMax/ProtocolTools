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
        CurrentStatusText,
        ConfiguredStatusText,
    };
public:
    explicit SensorConfigureModel(QObject *parent = nullptr);
    ~SensorConfigureModel() override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void appendSensors(int count);
    Q_INVOKABLE void appendSensors(int beginNum, int count);
    Q_INVOKABLE void removeSensor(int index);
    Q_INVOKABLE void removeAll();

    Q_INVOKABLE void setVersion(int idx, const QString& hardware, const QString& software, const QString& product);
    Q_INVOKABLE void setState(int idx, int curState, int confState);
    Q_INVOKABLE void setAddress(int idx, int addr);
    Q_INVOKABLE void setConfState(int idx, int state);
    Q_INVOKABLE QString getName(int idx);
    Q_INVOKABLE int getAddr(int idx);

    static QStringList CURSTATUSDESC;
    static QMap<int, QString> CONFIGSTATUSDESC;
signals:

public slots:

private:
    bool outOfRange(int index);
    QList<QSharedPointer<YBSensorData>> _ybSensorDataList;
};

#endif // SENSORCONFIGUREMODEL_H
