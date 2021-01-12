#ifndef CDTCYCLE_H
#define CDTCYCLE_H

#include "cdtprotocol.h"

class CDTCycle : public CDTProtocol
{
    Q_OBJECT
public:
    CDTCycle(const QSharedPointer<NetworkBase>& network, const QSharedPointer<SettingData>& settingData);
    ~CDTCycle() override;

    // CDTProtocol interface
    void run() override;
    void processFrame() override;
    void changedYXResponse(QList<InfoFieldEntity> &infoFieldList);
    void ykResponse(CDTFrame& frame) override;
    int findPositive(uint32_t num);

    // 遥控闭锁
    void ykNotAllow(int ptId);
    // 遥控全闭锁
    void ykAllNotAllow();

    // 非全部点遥控帧，则要传入点号
    CDTFrame createCycleYKFrame(bool isAllPoint, int ptId = -1);

private:

    bool m_isRunYK;

};

#endif // CDTCYCLE_H
