#include "interwfstrategy.h"
#include "cdtinteracte.h"

InterWFStrategy::InterWFStrategy(CDTInteracte *cdt, QObject *parent)
    : CDTWFStrategy (cdt, parent)
    , m_cdt(cdt)
{
    setParent(parent);
}

InterWFStrategy::~InterWFStrategy()
{

}

void InterWFStrategy::ykResponse(CDTFrame &frame)
{
    InfoFieldEntity firstInfoData = frame.infoFields.front();
    uint8_t funCode = firstInfoData.funCode;
    uint8_t ctrlCode = firstInfoData.dataArray[0];
    // true合,false开
    int ykAddr = firstInfoData.dataArray[2];
    ykAddr |= firstInfoData.dataArray[3] << 8;

    if (ykAddr > m_cdt->getPtCfg()->m_globalDiList->size()) {
        qInfo("未找到对应点号");
        return ;
    }

    // add 返回上级确认
    if (funCode == m_cdt->getPtCfg()->m_ykReqCode) {
        if (!m_cdt->isRunYK()) {// 接收到遥控选择
            // 直接返回校核
            m_cdt->ykSelectBack(ctrlCode, static_cast<uint8_t>(ykAddr));
            // 进入遥控执行状态
            m_cdt->setRunYK(true);
        }
        else {// 接收到遥控执行
            m_cdt->ykExecuteBack(ctrlCode, static_cast<uint8_t>(ykAddr));
            // 退出遥控执行状态
            m_cdt->setRunYK(false);
        }
    }

}

void InterWFStrategy::sendYK(int ptId, bool offon)
{
    Q_UNUSED(ptId)
    Q_UNUSED(offon)
}
