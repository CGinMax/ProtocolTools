#include "expandwidget.h"
#include "ui_expandwidget.h"
#include <QVBoxLayout>
#include <QList>
#include "expandwidgetitem.h"

ExpandWidget::ExpandWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ExpandWidget)
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
    ui->scrollLayout->addWidget(item);
    m_itemList.append(item);
}

void ExpandWidget::insertExpandItem(int index, ExpandWidgetItem *item)
{
    if (item == nullptr) {
        return;
    }
    ui->scrollLayout->insertWidget(index, item);
    m_itemList.insert(index, item);
}

int ExpandWidget::indexOf(ExpandWidgetItem *item)
{
    if (item == nullptr) {
        return -1;
    }

    return m_itemList.indexOf(item);
}
