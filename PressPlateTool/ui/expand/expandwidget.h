#ifndef EXPANDWIDGET_H
#define EXPANDWIDGET_H

#include <QWidget>
#include <QScrollArea>

class GatherData;
class QVBoxLayout;
class ExpandWidgetItem;
class PortParam;
namespace Ui {
class ExpandWidget;
}

class ExpandWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ExpandWidget(QWidget *parent = nullptr);
    ~ExpandWidget() override;
    void addExpandItem(ExpandWidgetItem* item);
    void insertExpandItem(int index, ExpandWidgetItem* item);
    void removeExpandItem(ExpandWidgetItem* item);
    int indexOf(ExpandWidgetItem* item);


    static ExpandWidgetItem* createExpandWidget(const PortParam& portParam, const QString& name = tr("untitled"), int radius = 8);
signals:
    void itemChanged(const QSharedPointer<GatherData>& gatherData);

public slots:
    void onNotifySelected(ExpandWidgetItem* item);


protected:
    Ui::ExpandWidget* ui;
    QList<ExpandWidgetItem*> m_itemList;
    ExpandWidgetItem* m_checkItem;
};

#endif // EXPANDWIDGET_H
