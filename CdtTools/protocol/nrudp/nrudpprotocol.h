#ifndef NRUDPPROTOCOL_H
#define NRUDPPROTOCOL_H

#include <QQueue>
#include <QSharedPointer>
#include "nrudpframe.h"
#include "../protocolbase.h"
#include "../../enums.h"

class NrUdpProtocol : public ProtocolBase
{
    Q_OBJECT
public:
    NrUdpProtocol(const QSharedPointer<NetworkBase>& network, const QSharedPointer<SettingData>& settingData);
    ~NrUdpProtocol() override;

    void initStrategy() override;

    void run() override;

    void parseRecvData();

    NrUdpFrame::eNrParseResult parseToFrame();

    void processFrame();

    void send(const NrUdpFrame& frame);

    void yxResponse(QByteArray& infoData);

    void ycResponse(QByteArray& infoData);

    void ykRequest(int ptId, bool offon);

    void vyxResponse(QByteArray& infoData);

    void sendAllDi();

    void sendAllAi();

    void sendVDi();

    void uploadDiAi();

    void uploadVDi();

    NrUdpFrame buildYXFrame(uint8_t cmdCode, QList<DiData *> &ptList);

    inline PtCfg* getPtCfg() {
        return m_settingData->m_ptCfg.data();
    }

    inline void setRunYK(bool running) {
        m_isRunYK = running;
    }

    inline bool getRunYK() const {
        return m_isRunYK;
    }

signals:
public slots:
    void onReverseYx(int ptId, bool allow) override;
    void onReadyRead() override;
    void onDisconnected() override;
protected slots:
    void onTimeout() override;

private:
    QByteArray m_recvBuffer;
    QQueue<NrUdpFrame> m_frameQueue;
    uint m_sendCounter;
    bool m_isRunYK;
};

#endif // NRUDPPROTOCOL_H
