#include "nrudpwfstrategy.h"
#include "nrudpprotocol.h"

NrUdpWFStrategy::NrUdpWFStrategy(NrUdpProtocol* nrudp)
    : m_nrudp(nrudp)
{

}


void NrUdpWFStrategy::uploadTiming()
{
    if (!m_nrudp->getRunYK()) {
        m_nrudp->uploadVDi();
    }
}

void NrUdpWFStrategy::ykResponse(CDTFrame &frame)
{
    Q_UNUSED(frame)
}

void NrUdpWFStrategy::ykResponse(QByteArray &infoData)
{
    if ((infoData.at(11) & 0xFF) == 0x02) {
        int ykAddr = infoData.at(16) & 0xFF;
        ykAddr |= static_cast<int>(infoData.at(17) & 0xFF) << 8;
        bool status = (infoData.at(18) & 0xFF) == 1;
        if (ykAddr > m_nrudp->getPtCfg()->m_globalDiList->size()
                && ykAddr < m_nrudp->getPtCfg()->m_globalDiList->size())
            return ;

        emit m_nrudp->sendYKMsg(QStringLiteral("接收到请求五防解锁，点%1遥控%2操作").arg(ykAddr).arg(status ? QStringLiteral("分->合") : QStringLiteral("合->分")));
        m_nrudp->setRunYK(true);
        emit m_nrudp->notifyYK(ykAddr);
    }
}

void NrUdpWFStrategy::onLockOrUnlock(bool locked)
{
    Q_UNUSED(locked)
}

void NrUdpWFStrategy::sendYK(int ptId, bool offon)
{
    Q_UNUSED(ptId)
    Q_UNUSED(offon)
}
