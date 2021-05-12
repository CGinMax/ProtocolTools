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
    explicit SerialPortDialog(bool isMulti = false, QWidget *parent = nullptr);
    ~SerialPortDialog();

    PortParam portParam() const;
    int gatherNum() const;

private slots:
    void on_btnOk_clicked();

    void on_btnCancel_clicked();

private:
    Ui::SerialPortDialog *ui;
    PortParam m_portParam;
    int m_gatherNum;
};

#endif // SERIALPORTDIALOG_H
