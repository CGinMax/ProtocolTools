#include "floatbuttongroup.h"
#include <QPropertyAnimation>

FloatButtonGroup::FloatButtonGroup(QWidget *parent)
    : QWidget(parent)
    , m_layout(new QHBoxLayout(this))
{
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(5);
    setLayout(m_layout);
    resize(0, 0);
}

FloatButtonGroup::~FloatButtonGroup()
{

}

void FloatButtonGroup::setLayoutSpacing(int spacing)
{
    m_layout->setSpacing(spacing);
}

void FloatButtonGroup::addButton(QAbstractButton *btn)
{
    m_layout->addWidget(btn);
    resize(width() + btn->width(), height() + btn->height());
}

void FloatButtonGroup::insertButton(int index, QAbstractButton *btn)
{
    m_layout->insertWidget(index, btn);
    resize(width() + btn->width(), height() + btn->height());
}

void FloatButtonGroup::enterEvent(QEvent *event)
{
    for (int i = 0; i < m_layout->count(); i++) {
        auto widget = m_layout->takeAt(i)->widget();
        widget->setWindowOpacity(1.0);
    }

}

void FloatButtonGroup::leaveEvent(QEvent *event)
{
    for (int i = 0; i < m_layout->count(); i++) {
        auto widget = m_layout->takeAt(i)->widget();
        widget->setWindowOpacity(0.3);
    }
}
