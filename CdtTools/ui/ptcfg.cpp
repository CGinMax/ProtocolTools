#include "ptcfg.h"

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
    for (auto& di : *m_globalDiList) {
        m_diMap.insert(di->io(), di);
    }
    for (auto& ai : *m_globalAiList) {
        m_aiMap.insert(ai->io(), ai);
    }
    for(auto& vdi : *m_globalVDiList) {
        m_vdiMap.insert(vdi->io(), vdi);
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
