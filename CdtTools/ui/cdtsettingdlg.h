#ifndef CDTSETTINGDLG_H
#define CDTSETTINGDLG_H

#include <QDialog>
#include "ptcfg.h"


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



private slots:
    void on_btnReset_clicked();

    void on_btnOk_clicked();

    void on_btnCancel_clicked();


private:
    QSharedPointer<PtCfg> m_ptCfg;
    Ui::CDTSettingDlg *ui;
};

#endif // CDTSETTINGDLG_H
