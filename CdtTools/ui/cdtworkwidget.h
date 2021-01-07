#ifndef CDTWORKWIDGET_H
#define CDTWORKWIDGET_H

#include <QWidget>
#include <QScopedPointer>
#include <QTimer>
#include "../protocol/protocolbase.h"
#include "ptcfg.h"

QT_FORWARD_DECLARE_CLASS(DiTableModel);
QT_FORWARD_DECLARE_CLASS(AiTableModel);

namespace Ui {
    class CDTWorkWidget;
} // namespace Ui

class CDTWorkWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CDTWorkWidget(const QSharedPointer<PtCfg>& ptcfg, ProtocolBase* protocol, QWidget *parent = nullptr);
    ~CDTWorkWidget() override;


    void resetAiRandom(bool start);
signals:

public slots:

private:
    DiTableModel* m_diModel;
    AiTableModel* m_aiModel;
    DiTableModel* m_vyxModel;
    QTimer m_aiTimer;
    ProtocolBase* m_protocol;
    QScopedPointer<Ui::CDTWorkWidget> ui;

};

#endif // CDTWORKWIDGET_H
