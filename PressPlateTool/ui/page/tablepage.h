#ifndef TABLEPAGE_H
#define TABLEPAGE_H

#include <QWidget>
#include <memory>
#include "../base/base_type.h"
#include "../tables/ybtableview.h"

namespace Ui {
class TablePage;
}

class GatherController;
class IContent;

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

    void showErrorSnackBar(const QString& text, const QIcon& icon = QIcon());

    void queryStatusImple(int index, int addr, Fn<void(std::shared_ptr<IContent>)> success, Fn<void()> error);

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

    void on_editBegin_valueChanged(int value);

private:
    Ui::TablePage *ui;
    int m_currentIndex;
    int m_currentConfAddr;

    YBTableView* m_table;
    GatherController* m_controller;
};

#endif // TABLEPAGE_H
