#include "ptcfg.h"

PtCfg::PtCfg()
    : m_globalDiList(new QList<DiData*>)
    , m_globalAiList(new QList<AiData*>)
{
    m_globalDiList->append(new DiData());
    m_globalAiList->append(new AiData());
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
    delete m_globalDiList;
    m_globalDiList = nullptr;
    delete m_globalAiList;
    m_globalAiList = nullptr;

    m_diMap.clear();
    m_aiMap.clear();
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
