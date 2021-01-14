#ifndef CDTWORKWIDGET_H
#define CDTWORKWIDGET_H

#include <QWidget>
#include <QScopedPointer>
#include <QTimer>
#include <QCheckBox>
#include "../protocol/protocolbase.h"
#include "ptcfg.h"

QT_FORWARD_DECLARE_CLASS(DiTableModel);
QT_FORWARD_DECLARE_CLASS(AiTableModel);

namespace Ui {
    class CDTWorkWidget;
}

class CDTWorkWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CDTWorkWidget(const QSharedPointer<NetworkBase>& network, const QSharedPointer<SettingData>& settingData, QWidget *parent = nullptr);
    ~CDTWorkWidget() override;

    void resetAiRandom(bool start);
    void stopCommunication();
    bool isConnection();

signals:
    void stop();
    void startYK(int ptId, bool offon);

public slots:
    void recvMessage(const QString& msg);
    void on_btnExecute_clicked();

private:
    DiTableModel* m_diModel;
    AiTableModel* m_aiModel;
    DiTableModel* m_vyxModel;
    QCheckBox* m_cbRandom;
    QTimer m_viewTimer;
    ProtocolBase* m_protocol;
    QSharedPointer<NetworkBase> m_network;
    QScopedPointer<Ui::CDTWorkWidget> ui;

};

#endif // CDTWORKWIDGET_H
