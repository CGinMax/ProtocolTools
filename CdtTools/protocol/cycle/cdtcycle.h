#ifndef CDTCYCLE_H
#define CDTCYCLE_H

#include "../standard/cdtprotocol.h"

class CDTCycle : public CDTProtocol
{
    Q_OBJECT
public:
    CDTCycle(const QSharedPointer<NetworkBase>& network, const QSharedPointer<SettingData>& settingData);
    ~CDTCycle() override;

    void init() override;

    void ykUnlock(int ptId);

    void yKLock(int ptId);

    void yKAllLock();

    // 非全部点遥控帧，则要传入点号
    CDTFrame createCycleYKFrame(bool isAllPoint, int ptId = -1);
    void uploadLock();

public slots:
protected slots:
    void onTimeout() override;

private:
    int m_cycleTime;
    int m_cycleTimer;
};

#endif // CDTCYCLE_H
