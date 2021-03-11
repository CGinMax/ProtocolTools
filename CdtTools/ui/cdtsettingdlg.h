#ifndef CDTSETTINGDLG_H
#define CDTSETTINGDLG_H

#include <QDialog>
#include "../common/ptcfg.h"


namespace Ui {
class CDTSettingDlg;
}

class CDTSettingDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CDTSettingDlg(const QSharedPointer<PtCfg>& ptcfg, QWidget *parent = nullptr);
    ~CDTSettingDlg() override;

    void initWidgetData(const PtCfg& setting);

    static QVector<PtCfg*> s_defaultCfgs;
    void initDefaultCfgs();

private slots:
    void on_btnReset_clicked();

    void on_btnOk_clicked();

    void on_btnCancel_clicked();

    void on_cbbProtocol_currentIndexChanged(int index);

private:
    QSharedPointer<PtCfg> m_ptCfg;
    Ui::CDTSettingDlg *ui;
};

#endif // CDTSETTINGDLG_H
