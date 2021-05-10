#ifndef SERIALPORTDIALOG_H
#define SERIALPORTDIALOG_H

#include <QDialog>
#include "portparam.h"

namespace Ui {
class SerialPortDialog;
}

class SerialPortDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SerialPortDialog(QWidget *parent = nullptr);
    ~SerialPortDialog();

    PortParam portParam() const;

private slots:
    void on_btnOk_clicked();

    void on_btnCancel_clicked();

private:
    Ui::SerialPortDialog *ui;
    PortParam m_portParam;
};

#endif // SERIALPORTDIALOG_H
