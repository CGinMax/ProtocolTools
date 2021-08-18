#ifndef CDTSETTINGDLG_H
#define CDTSETTINGDLG_H

#include <QDialog>
#include "../common/ptcfg.h"


namespace Ui {
class CDTSettingDlg;
}

QT_FORWARD_DECLARE_CLASS(QLabel)

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

    void on_btnYxImportSheet_clicked();

    void on_btnYcImportSheet_clicked();

    void on_btnVYxImportSheet_clicked();
private:
    QList<QByteArray> readDataFromSelectedFile(QLabel* infoLabel);
    QString getSheetFileName();
    QList<QByteArray> readFileData(const QString& filename);

    /**
     * @brief parseLineDataVaild 解析点表单行数据
     * @param lineData           读取到的单行数据
     * @return
     */
    bool parseLineDataVaild(const QByteArray& lineData);
private:
    QSharedPointer<PtCfg> m_ptCfg;
    Ui::CDTSettingDlg *ui;
    QList<DiData> m_confDiDatas;
    QList<AiData> m_confAiDatas;
    QList<DiData> m_confVDiDatas;
};

#endif // CDTSETTINGDLG_H
