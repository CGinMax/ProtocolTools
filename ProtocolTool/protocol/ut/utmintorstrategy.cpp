#include "utmintorstrategy.h"
#include "cdtexut.h"

UtMintorStrategy::UtMintorStrategy(CDTExUt *cdt, QObject *parent)
    : CDTMintorStrategy(cdt, parent)
    , m_cdt(cdt)
{

}

UtMintorStrategy::~UtMintorStrategy()
{

}

void UtMintorStrategy::ykResponse(CDTFrame &frame)
{
    InfoFieldEntity firstInfoData = frame.infoFields.front();
    uint8_t funCode = firstInfoData.funCode;
    uint8_t ctrlCode = firstInfoData.dataArray[0];
    bool success = ctrlCode != 0xFF;
    // true合,false开
    bool status = ctrlCode == m_cdt->getPtCfg()->m_ykClose;
    int ykAddr = firstInfoData.dataArray[1];

    if (ykAddr > m_cdt->getPtCfg()->m_globalDiList->size())
        return ;

    if (funCode == m_cdt->getPtCfg()->m_ykAckCode) {
        // 遥控应答
        if (success) {
            emit m_cdt->sendYKMsg(QStringLiteral("接收到请求应答，允许点%1遥控变位操作").arg(ykAddr));
            auto di = m_cdt->getPtCfg()->findDiById(ykAddr);
            QString msg;
            if (di) {
                di->setValue(status);
                msg = QStringLiteral("变位成功");
            }
            else {
                msg = QStringLiteral("变位失败，遥信点Id=%1错误").arg(ykAddr);
            }
            emit m_cdt->sendYKMsg(msg);
        }
        else {
            emit m_cdt->sendYKMsg(QStringLiteral("接收到请求应答，禁止点%1遥控变位操作").arg(ykAddr));
        }
        m_cdt->setRunYK(false);
    }
}

void UtMintorStrategy::sendYK(int ptId, bool offon)
{
    if (ptId > m_cdt->getPtCfg()->m_globalDiList->last()->io())
        return ;

    eControlLockCode code = offon ? eControlLockCode::CloseValidLock : eControlLockCode::OpenValidLock;

    m_cdt->ykSelect(code, static_cast<uint8_t>(ptId));
    m_cdt->setRunYK(true);
}
