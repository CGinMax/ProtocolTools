#include "diheaderview.h"

DiHeaderView::DiHeaderView(Qt::Orientation orientation, QWidget *parent)
    : QHeaderView(orientation, parent)
    , m_cbb(new QComboBox(this))
{
    m_cbb->addItems({"分", "合"});
    connect(m_cbb.data(), QOverload<int>::of(&QComboBox::currentIndexChanged), this, &DiHeaderView::onCbbCurrentIndexChanged);
}

void DiHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    if (logicalIndex == 2) {
        m_cbb->setGeometry(rect);
        return ;
    }
    QHeaderView::paintSection(painter, rect, logicalIndex);

}

void DiHeaderView::onCbbCurrentIndexChanged(int index)
{
    emit notifyAllChanged(index == 1);
}
