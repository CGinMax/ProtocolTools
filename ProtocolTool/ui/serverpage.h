#ifndef SERVERPAGE_H
#define SERVERPAGE_H

#include <QWidget>
#include <QTcpServer>
#include <QTabWidget>
#include <QQueue>
#include "../../Communication/tcpserver.h"
#include "cdtworkwidget.h"
class QVBoxLayout;

class ServerPage : public QWidget
{
    Q_OBJECT
public:
    explicit ServerPage(const QSharedPointer<SettingData>& settingData, QWidget *parent = nullptr);
    ~ServerPage() override;

    void initTabWidget();

    bool start();
    bool start(const PortParam& param);

    void stopListen();
    void stop();
signals:

public slots:
    void onUpdateData();
    void onNewConnection();
    void onDisconnected();
    void onTabCloseRequested(int index);
    void onCloseDisconnected();

private:
    QSharedPointer<QTcpServer> m_tcpServer;
    QScopedPointer<QTabWidget> m_tabClients;
    QScopedPointer<CDTWorkWidget> m_centerWidget;
    QSharedPointer<SettingData> m_settingData;
    QQueue<CDTWorkWidget*> m_closedClient;
    QVBoxLayout* m_layout;
};

#endif // SERVERPAGE_H
