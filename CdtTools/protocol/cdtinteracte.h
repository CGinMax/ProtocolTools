#ifndef CDTINTERACTE_H
#define CDTINTERACTE_H

#include "cdtprotocol.h"

class CDTInteracte : public CDTProtocol
{
    Q_OBJECT
public:
    CDTInteracte(const QSharedPointer<NetworkBase>& network, const QSharedPointer<SettingData>& settingData);

    void ykResponse(CDTFrame& frame) override;
    // 遥控选择命令
    void ykSelect(uint8_t ctrlCode, uint8_t ptId);
    void ykSelectBack(uint8_t ctrlCode, uint8_t ptId);
    void ykExecute(uint8_t ctrlCode, uint8_t ptId);
    // 遥控解闭锁回应
    void ykExecuteBack(uint8_t ctrlCode, uint8_t ptId, bool success = true);

    // 遥控帧
    CDTFrame interactYKFrame(uint8_t frameType, uint8_t funCode, uint8_t operCode, uint8_t vaild, int ptId);

public slots:
    void startYK(int ptId, bool offon) override;

};

#endif // CDTINTERACTE_H
