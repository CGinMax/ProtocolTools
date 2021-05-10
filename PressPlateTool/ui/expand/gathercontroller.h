#ifndef GATHERCONTROLLER_H
#define GATHERCONTROLLER_H

#include <QObject>
#include <functional>
#include <QSharedPointer>
#include "../../common/gatherdata.h"
#include "../../protocol/ybprotocolchannel.h"

class ExpandTile;
class GatherOperWidget;

class GatherController : public QObject
{
    Q_OBJECT
public:
    explicit GatherController(GatherData* data, QObject *parent = nullptr);
    ~GatherController() override;

    QSharedPointer<GatherData> gatherData() const;
    void setGatherData(const QSharedPointer<GatherData> &gatherData);

    void setExpandTile(ExpandTile* tile);
    void setOperWidget(GatherOperWidget* operWidget);

    YBProtocolChannel* protocol();

    void processReply(ProtocolReply* reply, QObject* obj, std::function<void()> finishFun, std::function<void()> errorFun);
signals:

public slots:
    void onQueryVersion();
    void onTitleChanged(const QString& title);
    void onSetGatherAddress(int addr);
    void onResetSensorCount(int count);

private:
    QSharedPointer<GatherData> m_gatherData;
    ExpandTile* m_tile;
    GatherOperWidget* m_operWidget;
    QSharedPointer<CommunicationBase> m_communication;
    QScopedPointer<ProtocolChannelBase> m_protocol;
};

#endif // GATHERCONTROLLER_H
