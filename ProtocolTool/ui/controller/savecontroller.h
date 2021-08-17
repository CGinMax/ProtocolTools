#ifndef SAVECONTROLLER_H
#define SAVECONTROLLER_H

#include <QObject>
#include "../../common/ptcfg.h"

class SaveController : public QObject
{
    Q_OBJECT
public:
    explicit SaveController(QObject *parent);
    ~SaveController() = default;

    bool saveConfig(const QMultiMap<QString, SettingData*>& settingMap, const QString& saveFilePath);

    QMultiMap<QString, SettingData*> importConfig(const QString& importPath);

signals:
    void saveFinish(const QString& msg);
    void importFinish(const QMultiMap<QString, SettingData*>& settingMap);
public slots:
    void onActionImportTriggered();
    void onActionSaveTriggered(const QMultiMap<QString, SettingData*>& settingMap);

private:
    void onSaveFinish(const QString& msg);

private:
};

#endif // SAVECONTROLLER_H
