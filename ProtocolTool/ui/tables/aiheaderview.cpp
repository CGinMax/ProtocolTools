#include "aiheaderview.h"

AiHeaderView::AiHeaderView(Qt::Orientation orientation, QWidget *parent)
    : QHeaderView(orientation, parent)
    , m_chbRandom(new QCheckBox(this))
{
    m_chbRandom->setText(tr("Is Random"));
    connect(m_chbRandom.data(), &QCheckBox::toggled, this, &AiHeaderView::notifyIsRandom);
}

void AiHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    if (logicalIndex == 2) {
        m_chbRandom->setGeometry(rect);
        return;
    }

    QHeaderView::paintSection(painter, rect, logicalIndex);
}
