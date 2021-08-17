#ifndef TABPAGE_H
#define TABPAGE_H

#include <QWidget>
#include "serverpage.h"
#include "clientpage.h"
#include "udppage.h"
#include "serialportpage.h"
namespace Ui {
class TabPage;
}

class TabPage : public QWidget
{
    Q_OBJECT

public:
    explicit TabPage(const QString& name = tr("Default Page"), QWidget *parent = nullptr);
    explicit TabPage(const QSharedPointer<SettingData>& settingData, const QString& name, QWidget *parent = nullptr);
    ~TabPage() override;
    void initWidget();

    void resetSettingData();

    void setConfigureWidgetEnabled(bool enabled);

    void startCommunication();

    void stopCommunication();

    SettingData* getSettingData() const;

    void setPageName(const QString& name);
    QString getPageName() const;

signals:
    void updateData();
private slots:

    void on_btnStart_clicked();

    void on_btnStop_clicked();

    void on_btnSetting_clicked();

    void on_chbBaudRate_toggled(bool checked);

    void on_cbbUdpMode_currentIndexChanged(int index);

private:
    QSharedPointer<SettingData> m_settingData;
    QScopedPointer<ServerPage> m_serverPage;
    QScopedPointer<ClientPage> m_clientPage;
    QScopedPointer<UdpPage> m_udpPage;
    QScopedPointer<SerialPortPage> m_serialPage;
    QString m_pageName;
    eNetworkType m_networkType;
    Ui::TabPage *ui;
};

#endif // TABPAGE_H
