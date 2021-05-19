#include "slideanimation.h"
#include <QDebug>

Ui::SlideAnimation::SlideAnimation(const QPoint &pos, QObject *parent)
    : QPropertyAnimation(parent)
    , m_sourcePos(pos)
{
}

void Ui::SlideAnimation::setSourcePos(const QPoint &pos)
{
    m_sourcePos = pos;
}


QVariant Ui::SlideAnimation::interpolated(const QVariant &from, const QVariant &to, qreal progress) const
{
    QPoint posStart = from.toPoint();
    QPoint posStop = to.toPoint();
    QPoint p(m_sourcePos.x() + (posStop.x() - posStart.x()) * progress,
                  m_sourcePos.y() + (posStop.y() - posStart.y()) * progress);

    return p;
}
