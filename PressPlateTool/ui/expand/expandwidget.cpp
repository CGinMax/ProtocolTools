#include "expandwidget.h"
#include "ui_expandwidget.h"
#include <QVBoxLayout>
#include <QList>
#include "expandwidgetitem.h"
#include "gatheroperwidget.h"
#include "gathercontroller.h"
#include <QMetaType>
#include <QScrollBar>
ExpandWidget::ExpandWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ExpandWidget)
    , m_checkItem(nullptr)
{
    qRegisterMetaType<QSharedPointer<GatherData> >("const QSharedPointer<GatherData> &");
    ui->setupUi(this);

    setStyleSheet("QWidget#scrollAreaWidgetContents{background-color:#F0F3F4;}");
}

ExpandWidget::~ExpandWidget()
{
    qDeleteAll(m_itemList);
    m_itemList.clear();
}

void ExpandWidget::addExpandItem(ExpandWidgetItem *item)
{
    if (item == nullptr) {
        return;
    }
    ui->scrollLayout->insertWidget(ui->scrollLayout->count() - 1, item);
    m_itemList.append(item);
    onNotifySelected(item);
    connect(item, &ExpandWidgetItem::notifySelected, this, &ExpandWidget::onNotifySelected);
    connect(item, &ExpandWidgetItem::deleteItem, this, &ExpandWidget::onDeleteItem);

//    ui->scrollAreaWidgetContents->setMinimumWidth(item->sizeHint().width());
//    ui->scrollArea->verticalScrollBar()->setSliderPosition(ui->scrollArea->verticalScrollBar()->sliderPosition() + item->height());
//    ui->scrollArea->update();
}

void ExpandWidget::insertExpandItem(int index, ExpandWidgetItem *item)
{
    if (item == nullptr) {
        return;
    }
    ui->scrollLayout->insertWidget(index, item);
    m_itemList.insert(index, item);
    onNotifySelected(item);
    connect(item, &ExpandWidgetItem::notifySelected, this, &ExpandWidget::onNotifySelected);
}

void ExpandWidget::removeExpandItem(ExpandWidgetItem* item)
{
    if (m_checkItem && m_checkItem == item) {
        auto index = indexOf(item);
        if (index == 0 && m_itemList.count() == 1) {
            m_checkItem = nullptr;
            onNotifySelected(nullptr);
        } else if (index == 0){
            onNotifySelected(m_itemList.at(index + 1));
        } else {
            onNotifySelected(m_itemList.at(index - 1));
        }
    }

    ui->scrollLayout->removeWidget(item);
    m_itemList.removeOne(item);
    delete item;
}

void ExpandWidget::removeAllItem()
{
    m_checkItem = nullptr;
    for (auto& item : m_itemList) {
        ui->scrollLayout->removeWidget(item);
        delete item;
    }
    m_itemList.clear();
    onNotifySelected(nullptr);
}

int ExpandWidget::indexOf(ExpandWidgetItem *item)
{
    if (item == nullptr) {
        return -1;
    }

    return m_itemList.indexOf(item);
}

QList<ExpandWidgetItem *> ExpandWidget::itemList() const
{
    return m_itemList;
}

void ExpandWidget::addExpandItems(const QList<QSharedPointer<GatherData> > &dataList)
{
    for (auto& data : dataList) {
        auto controller = new GatherController(data);
        auto tile = new ExpandTile(QObject::tr("Gather%1").arg(data->addr()));
        auto widget = new ExpandWidgetItem(tile, controller);
        auto operWidget = new GatherOperWidget(data->addr(), widget);
        widget->setBorderRadius(8);
        widget->setContentWidget(operWidget);
        controller->setExpandTile(tile);
        controller->setOperWidget(operWidget);
        addExpandItem(widget);
    }
}

ExpandWidgetItem *ExpandWidget::createExpandWidget(const PortParam &portParam, int index, int radius)
{
    auto data = new GatherData(QObject::tr("Gather%1").arg(index));
    data->setPortParam(portParam);
    auto controller = new GatherController(QSharedPointer<GatherData>(data));
    auto tile = new ExpandTile(QObject::tr("Gather%1").arg(index));
    auto widget = new ExpandWidgetItem(tile, controller);
    auto operWidget = new GatherOperWidget(index, widget);
    widget->setBorderRadius(radius);
    widget->setContentWidget(operWidget);
    controller->setExpandTile(tile);
    controller->setOperWidget(operWidget);

    return widget;
}

void ExpandWidget::onNotifySelected(ExpandWidgetItem *item)
{
    if (m_checkItem) {
        m_checkItem->setIsSelected(false);
    }
    m_checkItem = item;
    if (item == nullptr) {
        emit itemChanged(nullptr);
        return;
    }
    m_checkItem->setIsSelected(true);
    emit itemChanged(m_checkItem->getController());
}

void ExpandWidget::onDeleteItem()
{
    auto item = qobject_cast<ExpandWidgetItem*>(sender());
    removeExpandItem(item);
}
