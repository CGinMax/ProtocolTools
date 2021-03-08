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

    void send(const QByteArray& sendBytes);

    void yxResponse(QByteArray& infoData);

    void ycResponse(QByteArray& infoData);

    void ykRequest(int ptId, bool offon);

    void vyxResponse(QByteArray& infoData);

    void sendAllDi();

    void sendAllAi();

    void sendVDi();

    void uploadDi();

    void uploadAi();

    void uploadVDi();

    static NrUdpFrame buildYXFrame(uint8_t cmdCode, QList<DiData *> &ptList);

    static NrUdpFrame buildYCFrame(uint8_t cmdCode, QList<AiData *> &ptList);

    static QByteArray buildYXProtocol(const QSharedPointer<SettingData>& settingData);

    static QByteArray buildYCProtocol(const QSharedPointer<SettingData>& settingData);

    static QByteArray buildVYXProtocol(const QSharedPointer<SettingData>& settingData);

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
    void onRecvBytes(const QByteArray& bytes);
    void onDisconnected() override;
protected slots:
    void onTimeout() override;

private:
    QByteArray m_recvBuffer;
    QQueue<NrUdpFrame> m_frameQueue;
    uint m_yxSendCounter;
    uint m_ycSendCounter;
    uint m_vyxSendCounter;
    bool m_isRunYK;
};

#endif // NRUDPPROTOCOL_H
