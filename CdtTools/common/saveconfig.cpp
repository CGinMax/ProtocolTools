#include "saveconfig.h"
#include <QDataStream>
#include <exception>
#include "../ui/tabpage.h"

SaveConfig::SaveConfig(QObject *parent) : QObject(parent)
{

}

bool SaveConfig::saveTabConfig(QMultiMap<QString, SettingData *> &settingMap, const QString &saveFilePath)
{
    QFile file(saveFilePath);
    if (!file.open(QFile::ReadWrite | QFile::Truncate)) {
        qDebug("Save failed!");
        throw "save " + saveFilePath.toStdString() + " failed";
    }

    QDataStream ds(&file);
    for (auto iter = settingMap.begin(); iter != settingMap.end(); iter++) {
        ds << iter.key();
        iter.value()->save(ds);
    }
    file.close();
    return true;
}

QMultiMap<QString, SettingData *> SaveConfig::import(const QString &importPath)
{
    QFile file(importPath);
    if (!file.open(QFile::ReadWrite)) {
        throw "open " + importPath.toStdString() + " failed";
    }

    QDataStream ds(&file);
    QMultiMap<QString, SettingData*> settingMap;
    while (!ds.atEnd()) {
        QString pageName;
        ds >> pageName;
        auto settingData = new SettingData();
        settingData->load(ds);
        settingData->m_ptCfg->resetPoints();
        settingMap.insert(pageName, settingData);
    }

    return settingMap;
}
