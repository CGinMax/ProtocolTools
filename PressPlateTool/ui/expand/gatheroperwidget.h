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

public slots:

private:
    Ui::GatherOperWidget* ui;
};

#endif // GATHEROPERWIDGET_H
