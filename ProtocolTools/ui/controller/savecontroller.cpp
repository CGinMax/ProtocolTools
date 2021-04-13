#include "savecontroller.h"
#include "../../common/threadpool.h"
#include <QDataStream>
#include <exception>

#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>

SaveController::SaveController(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<QMultiMap<QString, SettingData*>>("QMultiMap<QString, SettingData*>&");
    connect(this, &SaveController::saveFinish, this, &SaveController::onSaveFinish);
}

bool SaveController::saveConfig(const QMultiMap<QString, SettingData *> &settingMap, const QString &saveFilePath)
{
    QFile file(saveFilePath);
    if (!file.open(QFile::ReadWrite | QFile::Truncate)) {
        throw std::runtime_error("save " + saveFilePath.toStdString() + " failed");
    }

    QDataStream ds(&file);
    for (auto iter = settingMap.begin(); iter != settingMap.end(); iter++) {
        ds << iter.key();
        iter.value()->save(ds);
    }
    file.close();
    return true;
}

QMultiMap<QString, SettingData *> SaveController::importConfig(const QString &importPath)
{
    QFile file(importPath);
    if (!file.open(QFile::ReadWrite)) {
        throw std::runtime_error("open " + importPath.toStdString() + " failed");
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

void SaveController::onActionImportTriggered()
{
    auto sysDocumentPaths = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    auto openFileName = QFileDialog::getOpenFileName(nullptr, tr("Open")
                        , sysDocumentPaths.first(), QLatin1String("All Files (*.*)"));
    if (openFileName.isEmpty()){
        return ;
    }
    ThreadPool::instance()->run([=]{
        try {
            auto tabList = this->importConfig(openFileName);
            emit this->importFinish(tabList);

        } catch(std::exception& e) {
            qDebug("%s", e.what());
        }
    });
}

void SaveController::onActionSaveTriggered(const QMultiMap<QString, SettingData *> &settingMap)
{
    auto sysDocumentPaths = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    auto saveFileName = QFileDialog::getSaveFileName(nullptr, tr("Save")
                                                     , sysDocumentPaths.first() + tr("/untitled"), QLatin1String("All Files (*.*)"));
    if (saveFileName.isEmpty()) {
        return ;
    }
    ThreadPool::instance()->run([=]{
        bool success = false;
        try {
            success = this->saveConfig(settingMap, saveFileName);
        } catch (std::exception& e) {
            qDebug("%s", e.what());
        }
        emit this->saveFinish(success ? tr("Save %1 Success!").arg(saveFileName) : tr("Save %1 Failed!").arg(saveFileName));
    });
}

void SaveController::onSaveFinish(const QString &msg)
{
    QMessageBox::information(qobject_cast<QWidget*>(parent()), tr("Information"), msg, QMessageBox::Ok);
}
