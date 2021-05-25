#ifndef SERIALPORTDIALOG_H
#define SERIALPORTDIALOG_H

#include <QDialog>

namespace Ui {
class SerialPortDialog;
}

class PortParam;

class SerialPortDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SerialPortDialog(bool isMulti = false, QWidget *parent = nullptr);
    ~SerialPortDialog() override;

    PortParam portParam() const;
    int gatherNum() const;


private:
    Ui::SerialPortDialog *ui;
};

#endif // SERIALPORTDIALOG_H
