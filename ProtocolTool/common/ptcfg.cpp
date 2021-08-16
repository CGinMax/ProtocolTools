#include "ptcfg.h"
#include <QDataStream>

PtCfg::PtCfg()
    : m_globalDiList(new QList<DiData*>)
    , m_globalAiList(new QList<AiData*>)
    , m_globalVDiList(new QList<DiData*>)
{
    m_globalDiList->append(new DiData());
    m_globalAiList->append(new AiData());
    m_globalVDiList->append(new DiData());
    initMap();
}
PtCfg::~PtCfg() {
    clearPoints();
}

void PtCfg::initMap()
{
    m_diMap.clear();
    m_aiMap.clear();
    m_vdiMap.clear();
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
    clearYxPoints();

    clearYcPoints();

    clearVYxPoints();
}

void PtCfg::clearYxPoints()
{
    for (auto& di : *m_globalDiList) {
        delete di;
        di = nullptr;
    }
    m_globalDiList->clear();
    delete m_globalDiList;
    m_globalDiList = nullptr;
    m_diMap.clear();
}

void PtCfg::clearYcPoints()
{
    for (auto& ai : *m_globalAiList) {
        delete ai;
        ai = nullptr;
    }
    m_globalAiList->clear();

    delete m_globalAiList;
    m_globalAiList = nullptr;
    m_aiMap.clear();
}

void PtCfg::clearVYxPoints()
{
    for (auto& vdi : *m_globalVDiList) {
        delete vdi;
        vdi = nullptr;
    }
    m_globalVDiList->clear();

    delete m_globalVDiList;
    m_globalVDiList = nullptr;

    m_vdiMap.clear();
}

void PtCfg::resetPoints()
{
    clearPoints();

    m_globalDiList = new QList<DiData*>;
    for (int i = 0; i < m_yxNum; i++) {
        m_globalDiList->append(new DiData(m_yxStartIo + i, QString("Pt%1").arg(m_yxStartIo + i), false));
    }

    m_globalAiList = new QList<AiData*>;
    for (int i = 0; i < m_ycNum; i++) {
        m_globalAiList->append(new AiData(m_ycStartIo + i, QString("Pt%1").arg(m_ycStartIo + i), 0));
    }

    m_globalVDiList = new QList<DiData*>;
    for (int i = 0; i < m_vyxNum; i++) {
        m_globalVDiList->append(new DiData(m_vyxStartIo + i, QString("Pt%1").arg(m_vyxStartIo + i), 0));
    }
    initMap();
}

void PtCfg::resetPoints(const QList<DiData> &diDatas, const QList<AiData> &aiDatas, const QList<DiData> &vdiDatas)
{
    clearPoints();

    m_globalDiList = new QList<DiData*>;
    for (auto& di : diDatas) {
        m_globalDiList->append(new DiData(di));
    }

    m_globalAiList = new QList<AiData*>;
    for (auto& ai : aiDatas) {
        m_globalAiList->append(new AiData(ai));
    }

    m_globalVDiList = new QList<DiData*>;
    for (auto& vdi : vdiDatas) {
        m_globalVDiList->append(new DiData(vdi));
    }

    initMap();
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
               << m_ycFrameType << m_ycFuncode << m_ycNum << m_ycStartIo << m_ycTime
               << m_vyxFrameType << m_vyxFuncode << m_vyxNum << m_vyxStartIo << m_vyxTime
               << m_ykReqType << m_ykAckType << m_ykReqCode << m_ykAckCode << m_ykExeCode << m_ykClose << m_ykOpen << m_ykUnlock << m_ykLock;

    for (int i = 0; i < m_yxNum; i++) {
        dataStream << m_globalDiList->at(i)->io() << m_globalDiList->at(i)->name();
    }

    for (int i = 0; i < m_ycNum; i++) {
        dataStream << m_globalAiList->at(i)->io() << m_globalAiList->at(i)->name();
    }

    for (int i = 0; i < m_vyxNum; i++) {
        dataStream << m_globalVDiList->at(i)->io() << m_globalVDiList->at(i)->name();
    }
}

void PtCfg::load(QDataStream &dataStream)
{
    int protocolType = 0;
    dataStream >> protocolType >> m_controlType >> m_yxFrameType >> m_yxFuncode >> m_yxNum >> m_yxStartIo >> m_yxTime
               >> m_ycFrameType >> m_ycFuncode >> m_ycNum >> m_ycStartIo >> m_ycTime
               >> m_vyxFrameType >> m_vyxFuncode >> m_vyxNum >> m_vyxStartIo >> m_vyxTime
               >> m_ykReqType >> m_ykAckType >> m_ykReqCode >> m_ykAckCode >> m_ykExeCode >> m_ykClose >> m_ykOpen >> m_ykUnlock >> m_ykLock;
    m_protocol = eProtocol(protocolType);

    QList<DiData> diList;
    for (int i = 0; i < m_yxNum; i++) {
        QString name{QString()};
        int io = 0;
        dataStream >> io >> name;
        diList.append(DiData(io, name, false));
    }
    QList<AiData> aiList;
    for (int i = 0; i < m_ycNum; i++) {
        QString name{QString()};
        int io = 0;
        dataStream >> io >> name;
        aiList.append(AiData(io, name, 0.0));
    }
    QList<DiData> vdiList;
    for (int i = 0; i < m_vyxNum; i++) {
        QString name{QString()};
        int io = 0;
        dataStream >> io >> name;
        vdiList.append(DiData(io, name, false));
    }

    resetPoints(diList, aiList, vdiList);
}

void SettingData::save(QDataStream &dataStream)
{
    m_portParam.save(dataStream);
    dataStream << m_networkType << m_stationType;
    m_ptCfg->save(dataStream);
}

void SettingData::load(QDataStream &dataStream)
{
    int networkType = 0;
    int stationType = 0;
    m_portParam.load(dataStream);
    dataStream >> networkType >> stationType;
    m_networkType = eNetworkType(networkType);
    m_stationType = eStationType(stationType);
    m_ptCfg->load(dataStream);
}
