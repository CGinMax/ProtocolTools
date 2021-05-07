#ifndef GATHERDATA_H
#define GATHERDATA_H

#include <QObject>
#include "ybsensordata.h"

class GatherData : public QObject
{
    Q_OBJECT
public:
    explicit GatherData(QObject *parent = nullptr);

    QString id() const;
    void setId(const QString &id);

    QString addr() const;
    void setAddr(const QString &addr);

    QString version() const;
    void setVersion(const QString &version);

signals:

public slots:

private:
    QString m_id;
    QString m_addr;
    QString m_version;
    QList<YBSensorData> m_ybDataList;
};

#endif // YBGATHERDATA_H
