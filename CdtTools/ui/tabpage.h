#ifndef TABPAGE_H
#define TABPAGE_H

#include <QWidget>
#include "network/tcpserver.h"
#include "network/tcpclient.h"
#include "protocol/protocolbase.h"
#include "serverpage.h"
#include "clientpage.h"
namespace Ui {
class TabPage;
}

class TabPage : public QWidget
{
    Q_OBJECT

public:
    explicit TabPage(QWidget *parent = nullptr);
    ~TabPage() override;
    void initWidget();

    void resetSettingData();

    void setConfigureWidgetEnabled(bool enabled);

private slots:
    void on_cbbNetworkType_currentIndexChanged(int index);

    void on_btnStart_clicked();

    void on_btnStop_clicked();

    void on_btnSetting_clicked();

private:
    QSharedPointer<SettingData> m_settingData;
    QScopedPointer<ServerPage> m_serverPage;
    QScopedPointer<ClientPage> m_clientPage;
    Ui::TabPage *ui;
};

#endif // TABPAGE_H
