#ifndef SAVECONFIG_H
#define SAVECONFIG_H

#include <QObject>
#include "ptcfg.h"
class SaveConfig : public QObject
{
    Q_OBJECT
public:
    explicit SaveConfig(QObject *parent = nullptr);

    static bool save(SettingData* saveData, const QString& saveFilePath);

    static bool import(const QString& importPath);

signals:

public slots:
};

#endif // SAVECONFIG_H
