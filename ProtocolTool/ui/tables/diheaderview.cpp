#include "diheaderview.h"
DiHeaderView::DiHeaderView(Qt::Orientation orientation, QWidget *parent)
    : QHeaderView(orientation, parent)
    , m_swBtn(new SwitchButton(this))
{
    m_swBtn->setTrackMargins(QMargins(15, 5, 15, 5));
//    m_swBtn->setPenWidth(2);
    connect(m_swBtn.data(), &QAbstractButton::toggled, this, &DiHeaderView::notifyAllChanged);
}

void DiHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    if (logicalIndex == 2) {
        m_swBtn->setGeometry(rect);
        return ;
    }
    QHeaderView::paintSection(painter, rect, logicalIndex);

}
