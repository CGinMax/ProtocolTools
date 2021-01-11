#ifndef SERVERPAGE_H
#define SERVERPAGE_H

#include <QWidget>
#include <QTcpServer>
#include <QTabWidget>
#include "../enums.h"
#include "../common/threadpool.h"
#include "../protocol/protocolbase.h"
#include "../network/networkbase.h"
#include "../network/tcpserver.h"
#include "cdtworkwidget.h"

class ServerPage : public QWidget
{
    Q_OBJECT
public:
    explicit ServerPage(const QSharedPointer<SettingData>& settingData, QWidget *parent = nullptr);
    ~ServerPage() override;

    void start();
    void start(const QString& ip, int port);

    void stopListen();
    void stop();


signals:

public slots:
    void onNewConnection();
    void onTabCloseRequested(int index);

private:
    QScopedPointer<QTcpServer> m_tcpServer;
    //QScopedPointer<ThreadPool> m_socketPool;
    QScopedPointer<QTabWidget> m_tabClients;

    QScopedPointer<CDTWorkWidget> m_centerWidget;

    QSharedPointer<SettingData> m_settingData;
};

#endif // SERVERPAGE_H
