#include "cdtmintorstrategy.h"
#include "cdtprotocol.h"

CDTMintorStrategy::CDTMintorStrategy(CDTProtocol *cdt, QObject *parent)
    : m_cdt(cdt)
{
    setParent(parent);
}

CDTMintorStrategy::~CDTMintorStrategy()
{

}

void CDTMintorStrategy::uploadTiming()
{
    if (!m_cdt->isRunYK()) {
        m_cdt->uploadDi();
        m_cdt->uploadDi();
    }
}

void CDTMintorStrategy::ykResponse(CDTFrame &frame)
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
            return;
        }

        m_cdt->setRunYK(true);
        emit m_cdt->notifyYK(allowIndex);
        emit m_cdt->sendYKMsg(QStringLiteral("接收到点%1遥控变位请求").arg(allowIndex));
    }
}

int CDTMintorStrategy::findPositive(uint32_t num)
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
