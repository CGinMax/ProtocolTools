#include "intermintorstrategy.h"
#include "cdtinteracte.h"

InterMintorStrategy::InterMintorStrategy(CDTInteracte *cdt, QObject *parent)
    : CDTMintorStrategy (cdt, parent)
    , m_cdt(cdt)
{
    setParent(parent);
}

InterMintorStrategy::~InterMintorStrategy()
{

}

void InterMintorStrategy::ykResponse(CDTFrame &frame)
{
    InfoFieldEntity firstInfoData = frame.infoFields.front();
    uint8_t funCode = firstInfoData.funCode;
    uint8_t ctrlCode = firstInfoData.dataArray[0];
    // true合,false开
    bool status = ctrlCode == m_cdt->getPtCfg()->m_ykClose;
    int ykAddr = firstInfoData.dataArray[2];
    ykAddr |= firstInfoData.dataArray[3] << 8;

    if (ykAddr > m_cdt->getPtCfg()->m_globalDiList->size())
        return ;

    if (funCode == m_cdt->getPtCfg()->m_ykAckCode) {
        m_cdt->ykExecute(ctrlCode, static_cast<uint8_t>(ykAddr));
    }
    else if (funCode == m_cdt->getPtCfg()->m_ykExeCode) {
        bool success = firstInfoData.dataArray[1] == m_cdt->getPtCfg()->m_ykUnlock;
        if (success){
            auto di = m_cdt->getPtCfg()->findDiById(ykAddr);
            QString msg;
            if (di) {
                di->setValue(status);
                msg = QStringLiteral("变位成功");
            }
            else {
                msg = QStringLiteral("变位失败，遥信点Id=%1错误").arg(ykAddr);
            }
            m_cdt->emit sendYKMsg(msg);
        }
        else {
            m_cdt->emit sendYKMsg(QStringLiteral("禁止点%1遥控变位操作").arg(ykAddr));
        }
        m_cdt->setRunYK(false);
    }
}
