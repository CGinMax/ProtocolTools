#ifndef GATHEROPERWIDGET_H
#define GATHEROPERWIDGET_H

#include <QWidget>
namespace Ui {
class GatherOperWidget;
}
class GatherOperWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GatherOperWidget(QWidget *parent = nullptr);
    ~GatherOperWidget() override;

    int getInputAddress();

    void setButtonsOpened(bool isOpen);
signals:
    void setGatherAddress(int addr);
    void resetSensorCount(int count);

    void openCommunication();
    void closeCommunication();
public slots:

private slots:
    void on_btnSetAddr_clicked();

    void on_btnReset_clicked();

private:
    Ui::GatherOperWidget* ui;
};

#endif // GATHEROPERWIDGET_H
