#ifndef CDTWORKWIDGET_H
#define CDTWORKWIDGET_H

#include <QWidget>
#include <QScopedPointer>
#include <QTimer>
#include <QCheckBox>
#include "../protocol/protocolbase.h"
#include "floatbuttongroup.h"
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

    void startCommunication(const QSharedPointer<SettingData> &settingData);

    void resetAiRandom(bool start);
    void stopCommunication();
    bool isConnection();
protected:
    void resizeEvent(QResizeEvent *event) override;
signals:
    void stop();
    void startYK(int ptId, bool offon);
    void reverseYx(int ptId, bool allow);

public slots:
    void recvProtocolContent(const QString& msg);
    void recvYKMsg(const QString& msg);
    void onNotifyYK(int ptId);
private slots:
    void on_btnExecute_clicked();
    void onPlainTextContextMenuRequested(const QPoint &pos);
    void onTextBrowserContextMenuRequested(const QPoint &pos);

private:
    DiTableModel* m_diModel;
    AiTableModel* m_aiModel;
    DiTableModel* m_vyxModel;
    QTimer m_viewTimer;
    ProtocolBase* m_protocol;
    QSharedPointer<NetworkBase> m_network;
    QScopedPointer<FloatButtonGroup> m_floatBtnGroup;
    QScopedPointer<Ui::CDTWorkWidget> ui;


};

#endif // CDTWORKWIDGET_H
