#include "expandwidget.h"
#include "ui_expandwidget.h"
#include <QVBoxLayout>
#include <QList>
#include "expandwidgetitem.h"
#include "gatheroperwidget.h"

ExpandWidget::ExpandWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ExpandWidget)
    , m_checkItem(nullptr)
{
    ui->setupUi(this);
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
    if (m_checkItem) {
        m_checkItem->setIsSelected(false);
    }
    m_checkItem = item;
    m_checkItem->setIsSelected(true);
    connect(item, &ExpandWidgetItem::notifySelected, this, &ExpandWidget::onNotifySelected);
}

void ExpandWidget::insertExpandItem(int index, ExpandWidgetItem *item)
{
    if (item == nullptr) {
        return;
    }
    ui->scrollLayout->insertWidget(index, item);
    m_itemList.insert(index, item);

    if (m_checkItem) {
        m_checkItem->setIsSelected(false);
    }
    m_checkItem = item;
    m_checkItem->setIsSelected(true);
    connect(item, &ExpandWidgetItem::notifySelected, this, &ExpandWidget::onNotifySelected);
}

void ExpandWidget::removeExpandItem(ExpandWidgetItem* item)
{
    if (m_checkItem && m_checkItem == item) {
        m_checkItem->setIsSelected(false);
        auto index = indexOf(item);
        if (index == 0 && m_itemList.count() == 1) {
            m_checkItem = nullptr;
        } else if (index == 0){
            m_checkItem = m_itemList.at(index + 1);
            m_checkItem->setIsSelected(true);
        } else {
            m_checkItem = m_itemList.at(index - 1);
            m_checkItem->setIsSelected(true);
        }
    }

    //TODO(shijm): remove item
}

int ExpandWidget::indexOf(ExpandWidgetItem *item)
{
    if (item == nullptr) {
        return -1;
    }

    return m_itemList.indexOf(item);
}

ExpandWidgetItem *ExpandWidget::createExpandWidget(const QString &name, int radius)
{

    auto tile = new ExpandTile(name);
    auto widget = new ExpandWidgetItem(tile);
    widget->setBorderRadius(radius);
    widget->setContentWidget(new GatherOperWidget(widget));

    return widget;
}

void ExpandWidget::onNotifySelected()
{
    auto item = qobject_cast<ExpandWidgetItem*>(sender());
    if (m_checkItem) {
        m_checkItem->setIsSelected(false);
    }
    m_checkItem = item;
    m_checkItem->setIsSelected(true);
}
