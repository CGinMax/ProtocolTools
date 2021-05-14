#ifndef TABLEPAGE_H
#define TABLEPAGE_H

#include <QWidget>
#include <QPlainTextEdit>
#include "../tables/ybtableview.h"

namespace Ui {
class TablePage;
}

class GatherController;

class TablePage : public QWidget
{
    Q_OBJECT

public:
    explicit TablePage(QWidget *parent = nullptr);
    ~TablePage() override;

    void setGatherController(GatherController* controller);

private:
    void confAddrRecursion();

    void queryStatusRecursion();

    void queryVersionRecursion();

    bool canDoOperate();

public slots:
    void onSetSensorAddr(int index, int addr);

    void onQuerySensorStatus(int index, int addr);

    void onQuerySensorVersion(int index, int addr);

    void onChangeSensorStatus(int index, int addr, int status);

    void onShowProtocolMsg(const QString& msg);

private slots:
    void on_btnConfAllAddr_clicked();

    void on_btnQueryAllStatus_clicked();

    void on_btnQueryAllVer_clicked();

    void on_editBegin_valueChanged(int arg1);

private:
    Ui::TablePage *ui;
    QPlainTextEdit* m_textMsg;

    int m_currentIndex;
    int m_currentConfAddr;

    YBTableView* m_table;
    GatherController* m_controller;
};

#endif // TABLEPAGE_H
