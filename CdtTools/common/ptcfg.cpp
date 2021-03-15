#include "ptcfg.h"

PtCfg::PtCfg()
    : m_globalDiList(new QList<DiData*>)
    , m_globalAiList(new QList<AiData*>)
    , m_globalVDiList(new QList<DiData*>)
{
    m_globalDiList->append(new DiData());
    m_globalAiList->append(new AiData());
    m_globalVDiList->append(new DiData());
    qDebug("init Map");
    initMap();
}
PtCfg::~PtCfg() {
    clearPoints();
}

void PtCfg::initMap()
{
    for (int i = 0; i < m_globalDiList->size(); i++) {
        m_diMap.insert(m_globalDiList->at(i)->io(), m_globalDiList->at(i));
    }
    for (int i = 0; i < m_globalAiList->size(); i++) {
        m_aiMap.insert(m_globalAiList->at(i)->io(), m_globalAiList->at(i));
    }

    for (int i = 0; i < m_globalVDiList->size(); i++) {
        m_vdiMap.insert(m_globalVDiList->at(i)->io(), m_globalVDiList->at(i));
    }
}

void PtCfg::clearPoints()
{
    for (auto& di : *m_globalDiList) {
        delete di;
        di = nullptr;
    }
    m_globalDiList->clear();
    for (auto& ai : *m_globalAiList) {
        delete ai;
        ai = nullptr;
    }
    m_globalAiList->clear();
    for (auto& vdi : *m_globalVDiList) {
        delete vdi;
        vdi = nullptr;
    }
    m_globalVDiList->clear();

    delete m_globalDiList;
    m_globalDiList = nullptr;
    delete m_globalAiList;
    m_globalAiList = nullptr;
    delete m_globalVDiList;
    m_globalVDiList = nullptr;

    m_diMap.clear();
    m_aiMap.clear();
    m_vdiMap.clear();
}

DiData *PtCfg::findDiById(int id)
{
    auto iter = m_diMap.find(id);
    if (iter == m_diMap.end()) {
        return nullptr;
    }

    return iter.value();
}

AiData *PtCfg::findAiById(int id)
{
    auto iter = m_aiMap.find(id);
    if (iter == m_aiMap.end()) {
        return nullptr;
    }
    return iter.value();
}

DiData *PtCfg::findVDiById(int id)
{
    auto iter = m_vdiMap.find(id);
    if (iter == m_vdiMap.end()) {
        return nullptr;
    }
    return iter.value();
}

QMap<int, DiData *> PtCfg::getDiMap()
{
    return m_diMap;
}

QMap<int, AiData *> PtCfg::getAiMap()
{
    return m_aiMap;
}

QMap<int, DiData *> PtCfg::getVDiMap()
{
    return m_vdiMap;
}

void PtCfg::save(QDataStream &dataStream)
{
    dataStream << int(m_protocol) << m_controlType << m_yxFrameType << m_yxFuncode << m_yxNum << m_yxStartIo << m_yxTime
               << m_ycFrameType << m_ycFuncode << m_ycNum << m_ycStartIo << m_ycTime << m_isRandom
               << m_vyxFrameType << m_vyxFuncode << m_vyxNum << m_vyxStartIo << m_vyxTime
               << m_ykReqType << m_ykAckType << m_ykReqCode << m_ykAckCode << m_ykExeCode << m_ykClose << m_ykOpen << m_ykUnlock << m_ykLock;
}

void PtCfg::load(QDataStream &dataStream)
{
    int protocolType = 0;
    dataStream >> protocolType >> m_controlType >> m_yxFrameType >> m_yxFuncode >> m_yxNum >> m_yxStartIo >> m_yxTime
               >> m_ycFrameType >> m_ycFuncode >> m_ycNum >> m_ycStartIo >> m_ycTime >> m_isRandom
               >> m_vyxFrameType >> m_vyxFuncode >> m_vyxNum >> m_vyxStartIo >> m_vyxTime
               >> m_ykReqType >> m_ykAckType >> m_ykReqCode >> m_ykAckCode >> m_ykExeCode >> m_ykClose >> m_ykOpen >> m_ykUnlock >> m_ykLock;
    m_protocol = eProtocol(protocolType);
}

void SettingData::save(QDataStream &dataStream)
{
    dataStream << m_ip << m_port << m_remoteIp << m_remotePort << m_networkType << m_stationType;
    m_ptCfg->save(dataStream);
}

void SettingData::load(QDataStream &dataStream)
{
    int networkType = 0;
    int stationType = 0;
    dataStream >> m_ip >> m_port >> m_remoteIp >> m_remotePort >> networkType >> stationType;
    m_networkType = eNetworkType(networkType);
    m_stationType = eStationType(stationType);
    m_ptCfg->load(dataStream);
}
