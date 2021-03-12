#ifndef SAVECONFIG_H
#define SAVECONFIG_H

#include <QObject>
#include "ptcfg.h"

class TabPage;
class SaveConfig : public QObject
{
    Q_OBJECT
public:
    explicit SaveConfig(QObject *parent = nullptr);

    static bool saveTabConfig(SettingData* saveData, const QString& tabName, const QString& saveFilePath);

    static QMultiMap<QString, SettingData*> import(const QString& importPath);

signals:

public slots:
};

#endif // SAVECONFIG_H
