#ifndef SENSOROPERATIONDLG_H
#define SENSOROPERATIONDLG_H

#include <QDialog>

namespace Ui {
class SensorOperationDlg;
}

class SensorOperationDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SensorOperationDlg(const QString& title, const QString& info, QWidget *parent = nullptr);
    ~SensorOperationDlg() override;

private:
    Ui::SensorOperationDlg *ui;
};

#endif // SENSOROPERATIONDLG_H
