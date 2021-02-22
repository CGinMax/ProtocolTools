#ifndef PTCFG_H
#define PTCFG_H

#include "../enums.h"
#include <QSharedPointer>
#include <QPointer>
#include <QList>
#include <QMap>
#include "tables/aidata.h"
#include "tables/didata.h"

class PtCfg
{
public:
    PtCfg();
    ~PtCfg();


    void initMap();

    void clearPoints();

    DiData* findDiById(int id);

    AiData* findAiById(int id);

    DiData* findVDiById(int id);


    eProtocol m_protocol{eProtocol::CDTStandardary};
    uint8_t m_controlType{0x71};
    uint8_t m_yxFrameType{0xF4};
    uint8_t m_yxFuncode{0xF0};
    int m_yxNum{1};
    uint8_t m_yxStartIo{0};

    uint8_t m_ycFrameType{0x61};
    uint8_t m_ycFuncode{0x00};
    int m_ycNum{1};
    uint8_t m_ycStartIo{0};

    uint8_t m_vyxFrameType{0xF4};
    uint8_t m_vyxFuncode{0xF0};
    int m_vyxNum{1};
    uint8_t m_vyxStartIo{0};

    uint8_t m_ykReqType{0xF1};
    uint8_t m_ykAckType{0xF1};
    uint8_t m_ykReqCode{0xF0};
    uint8_t m_ykAckCode{0xF0};
    uint8_t m_ykExeCode{0x00};
    uint8_t m_ykClose{0xCC};
    uint8_t m_ykOpen{0x33};
    uint8_t m_ykUnlock{0xAA};
    uint8_t m_ykLock{0x55};

    int m_yxTime{1000};
    int m_ycTime{1000};
    int m_vyxTime{1000};

    bool m_isRandom{false};

    QList<DiData*>* m_globalDiList{nullptr};
    QList<AiData*>* m_globalAiList{nullptr};
    QList<DiData*>* m_globalVDiList{nullptr};

private:
    QMap<int, DiData*> m_diMap;
    QMap<int, AiData*> m_aiMap;
    QMap<int, DiData*> m_vdiMap;
};

struct SettingData{

    SettingData()
        : m_ptCfg(new PtCfg)
    {}

    QString m_ip{QLatin1Literal("0.0.0.0")};
    int m_port{2404};
    QString m_remoteIp{QLatin1String("0.0.0.0")};
    int m_remotePort{2406};
    eNetworkType m_networkType{eNetworkType::eTcpServer};
    eStationType m_stationType{eStationType::Minitor};
    QSharedPointer<PtCfg> m_ptCfg;
};

#endif // PTCFG_H
