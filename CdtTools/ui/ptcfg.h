#ifndef PTCFG_H
#define PTCFG_H

#include "../enums.h"
#include <QSharedPointer>
#include <QPointer>
#include <QList>
#include "tables/aidata.h"
#include "tables/didata.h"

struct PtCfg
{

    PtCfg()
        : m_globalDiList(new QList<DiData>)
        , m_globalAiList(new QList<AiData>)
    {
        m_globalDiList->append(DiData());
        m_globalAiList->append(AiData());
    }
    ~PtCfg() {
        delete m_globalDiList;
        m_globalDiList = nullptr;
        delete m_globalAiList;
        m_globalAiList = nullptr;
    }

    eProtocol m_protocol{eProtocol::CDTStandard};
    uint8_t m_controlType{0x71};
    uint8_t m_yxFrameType{0xF4};
    uint8_t m_yxFuncode{0xF0};
    uint8_t m_yxNum{1};
    uint8_t m_yxStartIo{0};

    uint8_t m_ycFrameType{0x61};
    uint8_t m_ycFuncode{0x00};
    uint8_t m_ycNum{1};
    uint8_t m_ycStartIo{0};

    uint8_t m_vyxFrameType{0xF4};
    uint8_t m_vyxFuncode{0xF0};
    uint8_t m_vyxNum{1};
    uint8_t m_vyxStartIo{0};

    uint8_t m_ykFrameType{0x57};
    uint8_t m_ykClose{0xCC};
    uint8_t m_ykOpen{0x33};
    uint8_t m_ykUnlock{0xAA};
    uint8_t m_ykLock{0x55};

    int m_yxTime{1000};
    int m_ycTime{1000};
    int m_vyxTime{1000};

    QList<DiData>* m_globalDiList{nullptr};
    QList<AiData>* m_globalAiList{nullptr};
};

struct SettingData{
    SettingData()
        : m_ptCfg(new PtCfg)
    {}

    QString m_ip{QLatin1Literal("0.0.0.0")};
    int m_port{2404};
    eNetworkType m_networkType{eNetworkType::eTcpServer};
    eStationType m_stationType{eStationType::Minitor};
    QSharedPointer<PtCfg> m_ptCfg;
};

#endif // PTCFG_H
