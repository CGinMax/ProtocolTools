#ifndef TABPAGE_H
#define TABPAGE_H

#include <QWidget>
#include "serverpage.h"
#include "clientpage.h"
#include "udppage.h"
namespace Ui {
class TabPage;
}

class TabPage : public QWidget
{
    Q_OBJECT

public:
    explicit TabPage(const QString& name = tr("Default Page"), QWidget *parent = nullptr);
    explicit TabPage(QSharedPointer<SettingData> settingData, const QString& name = tr("Default Page"), QWidget *parent = nullptr);
    ~TabPage() override;
    void initWidget();

    void resetSettingData();

    void setConfigureWidgetEnabled(bool enabled);

    SettingData* getSettingData() const;

    QString getPageName() const;

signals:
    void updateData();
private slots:
    void on_cbbNetworkType_currentIndexChanged(int index);

    void on_btnStart_clicked();

    void on_btnStop_clicked();

    void on_btnSetting_clicked();

private:
    QSharedPointer<SettingData> m_settingData;
    QScopedPointer<ServerPage> m_serverPage;
    QScopedPointer<ClientPage> m_clientPage;
    QScopedPointer<UdpPage> m_udpPage;
    QString m_pageName;
    Ui::TabPage *ui;
};

#endif // TABPAGE_H
