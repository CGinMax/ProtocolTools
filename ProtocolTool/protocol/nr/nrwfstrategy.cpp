#include "nrwfstrategy.h"
#include "cdtexnr.h"

NrWFStrategy::NrWFStrategy(CDTExNr *cdt, QObject *parent)
    : CDTWFStrategy (cdt, parent)
    , m_cdt(cdt)
{
    connect(&m_timer, &QTimer::timeout, this, &NrWFStrategy::onListenTimeout);
}

NrWFStrategy::~NrWFStrategy()
{

}

void NrWFStrategy::ykResponse(CDTFrame &frame)
{
    Q_UNUSED(frame);
}

void NrWFStrategy::onLockOrUnlock(bool locked)
{
    if (locked) {
        m_cdt->ykAllLock(0xFFFF);
        m_cdt->setRunYK(true);
    }
    else {
        m_cdt->ykAllUnlock(0xFEFF);
        m_cdt->setRunYK(false);
    }
}

void NrWFStrategy::sendYK(int ptId, bool /*offon*/)
{
    if (ptId > m_cdt->getPtCfg()->m_globalDiList->last()->io()) {
        return ;
    }

    if (!m_timer.isActive()) {
        m_listenPtId = ptId;
        m_oldStatus = m_cdt->getPtCfg()->findDiById(m_listenPtId)->value();
        m_timer.start(500);
    }
    m_cdt->ykExecute(ptId);

}

void NrWFStrategy::onListenTimeout()
{
    auto di = m_cdt->getPtCfg()->findDiById(m_listenPtId);
    if (di->value() == m_oldStatus) {
        return ;
    }
    emit m_cdt->sendYKMsg(QStringLiteral("已接收到点%1的遥信变位指令").arg(m_listenPtId));

    m_timer.stop();
}
