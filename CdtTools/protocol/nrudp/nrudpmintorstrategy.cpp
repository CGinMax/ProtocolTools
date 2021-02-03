#include "nrudpmintorstrategy.h"
#include "nrudpprotocol.h"

NrUdpMintorStrategy::NrUdpMintorStrategy(NrUdpProtocol *nrudp)
    : m_nrudp(nrudp)
    , m_oldPtId(0)
{

}


void NrUdpMintorStrategy::uploadTiming()
{
    if (!m_nrudp->getRunYK()) {
        m_nrudp->uploadDiAi();
    }
}

void NrUdpMintorStrategy::ykResponse(CDTFrame &frame)
{
    Q_UNUSED(frame)
}

void NrUdpMintorStrategy::ykResponse(QByteArray &infoData)
{
    bool success = true;
    if (infoData.at(11) == 0x03) {
        // allow
        success = true;
    }
    else if (infoData.at(11) == 0x04) {
        success = false;
    }
    if (success) {
        emit m_nrudp->sendYKMsg(QStringLiteral("接收到请求应答，允许点%1遥控变位操作").arg(m_oldPtId));
        auto di = m_nrudp->getPtCfg()->findDiById(m_oldPtId);
        QString msg;
        if (di) {
            di->setValue(!di->value());
            msg = QStringLiteral("遥控变位成功");
        }
        else {
            msg = QStringLiteral("遥控变位失败，遥信点Id=%1错误").arg(m_oldPtId);
        }
        emit m_nrudp->sendYKMsg(msg);
    }
    else {
        emit m_nrudp->sendYKMsg(QStringLiteral("接收到请求应答，禁止点%1遥控变位操作").arg(m_oldPtId));
    }
    m_nrudp->setRunYK(false);
}

void NrUdpMintorStrategy::onLockOrUnlock(bool locked)
{
    Q_UNUSED(locked)
}

void NrUdpMintorStrategy::sendYK(int ptId, bool offon)
{
    if (ptId > m_nrudp->getPtCfg()->m_globalDiList->last()->io()
            && ptId < m_nrudp->getPtCfg()->m_globalDiList->first()->io()) {
        return ;
    }
    m_oldPtId = ptId;
    m_nrudp->ykRequest(ptId, offon);
    m_nrudp->setRunYK(true);
}
