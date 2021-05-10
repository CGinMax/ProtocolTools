#ifndef GATHERDATA_H
#define GATHERDATA_H

#include <QObject>
#include "ybsensordata.h"
#include "portparam.h"

class GatherData : public QObject
{
    Q_OBJECT
public:
    explicit GatherData(const QString& name = QString(), QObject *parent = nullptr);
    ~GatherData() override;

    QString name() const;
    void setName(const QString& name);

    int id() const;
    void setId(int id);

    int addr() const;
    void setAddr(int addr);

    QString version() const;
    void setVersion(const QString &version);

    PortParam portParam() const;
    void setPortParam(const PortParam &portParam);

signals:
    void nameChanged(const QString& name);

    void addrChanged(int addr);

public slots:

private:
    QString m_name;
    int m_id;
    int m_addr;
    QString m_version;
    QList<YBSensorData> m_ybDataList;
    PortParam m_portParam;
};

#endif // YBGATHERDATA_H
