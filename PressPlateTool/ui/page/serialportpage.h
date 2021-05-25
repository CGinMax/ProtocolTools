#ifndef SERIALPORTPAGE_H
#define SERIALPORTPAGE_H

#include <QWidget>

namespace Ui {
class SerialPortPage;
}

class PortParam;

class SerialPortPage : public QWidget
{
    Q_OBJECT

public:
    explicit SerialPortPage(QWidget *parent = nullptr);
    ~SerialPortPage() override;

    void setCountEditHidden(bool isHidden);

    void setBtnGroupHidden(bool isHidden);

    int getGatherCount() const;

    PortParam getPortParam() const;
    void setPortParam(const PortParam& param);

signals:
    void okClicked();
    void cancelClicked();

private slots:
    void on_btnRefresh_clicked();

private:
    Ui::SerialPortPage *ui;
};

#endif // SERIALPORTPAGE_H
