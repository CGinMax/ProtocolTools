#ifndef CDTSTANDARD_H
#define CDTSTANDARD_H

#include "../standard/cdtprotocol.h"

class CDTStandard : public CDTProtocol
{
    Q_OBJECT
public:
    CDTStandard(const QSharedPointer<CommunicationBase>& network, const QSharedPointer<SettingData>& settingData);
    ~CDTStandard() override;

    void initStrategy() override;

    void ykUnlock(int ptId);

    void ykLock(int ptId);

    void ykAllLock();

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
