#ifndef TABLEPAGE_H
#define TABLEPAGE_H

#include <QWidget>
#include "../tables/ybtableview.h"

#include "../../protocol/ybprotocolchannel.h"
namespace Ui {
class TablePage;
}

class TablePage : public QWidget
{
    Q_OBJECT

public:
    explicit TablePage(QWidget *parent = nullptr);
    ~TablePage() override;

    void setProtocol(YBProtocolChannel* protocol);

private:
    void confAddrRecursion();

    void queryStatusRecursion();

    void queryVersionRecursion();

public slots:
    void onSetSensorAddr(int index, int addr);

    void onQuerySensorStatus(int index, int addr);

    void onQuerySensorVersion(int index, int addr);

    void onChangeSensorStatus(int index, int addr, int status);

private slots:
    void on_btnConfAllAddr_clicked();

    void on_btnQueryAllStatus_clicked();

    void on_btnQueryAllVer_clicked();

    void on_editBegin_valueChanged(int arg1);

private:
    Ui::TablePage *ui;

    int m_currentIndex;
    int m_currentConfAddr;

    YBTableView* m_table;
    YBProtocolChannel* m_protocol;
};

#endif // TABLEPAGE_H
