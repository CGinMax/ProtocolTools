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
signals:
    void setGatherAddress(int addr);
    void resetSensorCount(int count);
public slots:

private slots:
    void on_btnSetAddr_clicked();

    void on_btnReset_clicked();

private:
    Ui::GatherOperWidget* ui;
};

#endif // GATHEROPERWIDGET_H
