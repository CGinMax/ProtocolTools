#ifndef SENSORADDDIALOG_H
#define SENSORADDDIALOG_H

#include <QDialog>

namespace Ui {
class SensorAddDialog;
}

class SensorAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SensorAddDialog(QWidget *parent = nullptr);
    ~SensorAddDialog();

    int getCount();

private:
    Ui::SensorAddDialog *ui;
};

#endif // SENSORADDDIALOG_H
