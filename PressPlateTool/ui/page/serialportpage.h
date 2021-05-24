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

    PortParam getPortParam() const;

private:
    Ui::SerialPortPage *ui;
};

#endif // SERIALPORTPAGE_H
