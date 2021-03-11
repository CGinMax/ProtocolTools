#include "saveconfig.h"
#include <QSettings>

SaveConfig::SaveConfig(QObject *parent) : QObject(parent)
{

}

bool SaveConfig::save(SettingData *saveData, const QString &saveFilePath)
{
    QSettings saveSettings(saveFilePath, QSettings::IniFormat);
    saveSettings.setIniCodec("utf-8");
    saveSettings.beginGroup(QLatin1String("Network Settings"));

    saveSettings.setValue(QLatin1String("LocolIp"), saveData->m_ip);
    saveSettings.setValue(QLatin1String("LocalPort"), saveData->m_port);
    saveSettings.setValue(QLatin1String("RemoteIp"), saveData->m_remoteIp);
    saveSettings.setValue(QLatin1String("RemotePort"), saveData->m_remotePort);
    saveSettings.setValue(QLatin1String("NetworkType"), saveData->m_networkType);
    saveSettings.setValue(QLatin1String("StationType"), saveData->m_stationType);
    saveSettings.endGroup();

    saveSettings.beginGroup(QLatin1String("Protocol Settings"));

    saveSettings.setValue(QLatin1String("ProtocolType"), saveData->m_ptCfg->m_protocol);
    saveSettings.setValue(QLatin1String("ControlType"), saveData->m_ptCfg->m_controlType);
    saveSettings.setValue(QLatin1String("YXFrameType"), saveData->m_ptCfg->m_yxFrameType);
    saveSettings.setValue(QLatin1String("YXFunCode"), saveData->m_ptCfg->m_yxFuncode);
    saveSettings.setValue(QLatin1String("YXNum"), saveData->m_ptCfg->m_yxNum);
    saveSettings.setValue(QLatin1String("YXStartIO"), saveData->m_ptCfg->m_yxStartIo);
    saveSettings.setValue(QLatin1String("YXTime"), saveData->m_ptCfg->m_yxTime);

    saveSettings.setValue(QLatin1String("YCFrameType"), saveData->m_ptCfg->m_ycFrameType);
    saveSettings.setValue(QLatin1String("YCFunCode"), saveData->m_ptCfg->m_ycFuncode);
    saveSettings.setValue(QLatin1String("YCNum"), saveData->m_ptCfg->m_ycNum);
    saveSettings.setValue(QLatin1String("YCStartIO"), saveData->m_ptCfg->m_ycStartIo);
    saveSettings.setValue(QLatin1String("YCTime"), saveData->m_ptCfg->m_ycTime);

    saveSettings.setValue(QLatin1String("VYXFrameType"), saveData->m_ptCfg->m_vyxFrameType);
    saveSettings.setValue(QLatin1String("VYXFunCode"), saveData->m_ptCfg->m_vyxFuncode);
    saveSettings.setValue(QLatin1String("VYXNum"), saveData->m_ptCfg->m_vyxNum);
    saveSettings.setValue(QLatin1String("VYXStartIO"), saveData->m_ptCfg->m_vyxStartIo);
    saveSettings.setValue(QLatin1String("VYXTime"), saveData->m_ptCfg->m_vyxTime);

    saveSettings.setValue(QLatin1String("YKReqType"), saveData->m_ptCfg->m_ykReqType);
    saveSettings.setValue(QLatin1String("YKAckType"), saveData->m_ptCfg->m_ykAckType);
    saveSettings.setValue(QLatin1String("YKReqCode"), saveData->m_ptCfg->m_ykReqCode);
    saveSettings.setValue(QLatin1String("YKAckCode"), saveData->m_ptCfg->m_ykAckCode);
    saveSettings.setValue(QLatin1String("YKExeCode"), saveData->m_ptCfg->m_ykExeCode);
    saveSettings.setValue(QLatin1String("YKClose"), saveData->m_ptCfg->m_ykClose);
    saveSettings.setValue(QLatin1String("YKOpen"), saveData->m_ptCfg->m_ykOpen);
    saveSettings.setValue(QLatin1String("YKUnlock"), saveData->m_ptCfg->m_ykUnlock);
    saveSettings.setValue(QLatin1String("YKLock"), saveData->m_ptCfg->m_ykLock);

    saveSettings.setValue(QLatin1String("IsRandom"), saveData->m_ptCfg->m_isRandom);
    saveSettings.endGroup();
}

bool SaveConfig::import(const QString &importPath)
{

}
