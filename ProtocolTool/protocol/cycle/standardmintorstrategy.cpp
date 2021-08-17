#include "standardmintorstrategy.h"
#include "cdtstandard.h"

StandardMintorStrategy::StandardMintorStrategy(CDTStandard* cdt, QObject *parent)
    : CDTMintorStrategy (cdt, parent)
    , m_cdt(cdt)
{
    setParent(parent);
}

StandardMintorStrategy::~StandardMintorStrategy()
{

}

void StandardMintorStrategy::ykResponse(CDTFrame &frame)
{
    if (!m_cdt->isRunYK()) {
        // 解析报文，找解锁
        int allowIndex = -1;
        for (int idx = 0; idx < frame.infoFields.count(); idx++) {
            // 组合成一个四字节整数
            uint32_t combineNum = 0;
            for (int i = 0; i < 4; i++) {
                uint32_t convNum = frame.infoFields.at(idx).dataArray[i];
                combineNum |= convNum << i * 8;
            }
            // 提取里面是否有1的bit，有且只有一个
            auto positiveIdx = findPositive(combineNum);
            if (positiveIdx > -1) {
                allowIndex = idx * 32 + positiveIdx;
                break;
            }
        }

        // 闭锁或全闭锁
        if (allowIndex == -1) {
            emit m_cdt->sendYKMsg(QStringLiteral("接收到遥控闭锁指令!"));

            return;
        }

        m_cdt->setRunYK(true);
        emit m_cdt->notifyYK(allowIndex + m_cdt->getPtCfg()->m_globalDiList->first()->io());
        emit m_cdt->sendYKMsg(QStringLiteral("接收到点%1遥控变位请求").arg(allowIndex));
    }
}

int StandardMintorStrategy::findPositive(uint32_t num)
{
    if (num > 0) {
        for (int i = 0; i < 32; i++) {
            if ((num >> i) & 0x01) {
                return i;
            }
        }
    }
    return -1;
}

void StandardMintorStrategy::sendYK(int ptId, bool offon)
{
    Q_UNUSED(ptId)
    Q_UNUSED(offon)
}
