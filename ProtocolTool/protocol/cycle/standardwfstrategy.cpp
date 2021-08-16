#include "standardwfstrategy.h"
#include "cdtstandard.h"

StandardWFStrategy::StandardWFStrategy(CDTStandard *cdt, QObject *parent)
    : CDTWFStrategy (cdt, parent)
    , m_cdt(cdt)
    , m_listenPtId(0)
    , m_oldStatus(false)
{
    connect(&m_timer, &QTimer::timeout, this, &StandardWFStrategy::onListenTimeout);
}

StandardWFStrategy::~StandardWFStrategy()
{

}

void StandardWFStrategy::uploadTiming()
{
    if (!m_cdt->isRunYK()) {
        m_cdt->uploadLock();
    }
    CDTWFStrategy::uploadTiming();
}

void StandardWFStrategy::ykResponse(CDTFrame &frame)
{
    Q_UNUSED(frame)
}

void StandardWFStrategy::sendYK(int ptId, bool offon)
{
    Q_UNUSED(offon)

    if (ptId > m_cdt->getPtCfg()->m_globalDiList->last()->io()) {
        return ;
    }

    if (!m_timer.isActive()) {
        m_listenPtId = ptId;
        m_oldStatus = m_cdt->getPtCfg()->findDiById(m_listenPtId)->value();
        m_timer.start(500);
    }
    m_cdt->setRunYK(true);
    m_cdt->ykUnlock(ptId);

}

void StandardWFStrategy::onListenTimeout()
{
    auto di = m_cdt->getPtCfg()->findDiById(m_listenPtId);
    if (di->value() == m_oldStatus) {
        return ;
    }
    emit m_cdt->sendYKMsg(QStringLiteral("已接收到点%1的遥信变位指令").arg(m_listenPtId));
    m_cdt->ykLock(m_listenPtId);
    m_timer.stop();
    m_cdt->setRunYK(false);
}
