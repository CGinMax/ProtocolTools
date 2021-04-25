#include "switchbutton_internal.h"
#include "switchbutton.h"
#include <QGraphicsDropShadowEffect>
#include <QEvent>
#include <QPainter>

SwitchButtonThumb::SwitchButtonThumb(SwitchButton *parent)
    : QWidget(parent)
    , m_switchBtn(parent)
    , m_shift(0)
    , m_offset(0)
{
    Q_ASSERT(parent);

    auto effect = new QGraphicsDropShadowEffect(this);
    effect->setBlurRadius(6);
    effect->setColor(QColor(0, 0, 0, 80));
    effect->setOffset(QPointF(0, 1));
    setGraphicsEffect(effect);

    parent->installEventFilter(this);
}

SwitchButtonThumb::~SwitchButtonThumb()
{
}

void SwitchButtonThumb::setShift(qreal shift)
{
    if (m_shift == shift) {
        return ;
    }

    m_shift = shift;
    updateOffset();
}

bool SwitchButtonThumb::eventFilter(QObject *obj, QEvent *event)
{
    const QEvent::Type type = event->type();
    if (type == QEvent::Resize || type == QEvent::Move) {
        setGeometry(m_switchBtn->rect().adjusted(8, 8, -8, -8));
        updateOffset();
    }

    return QWidget::eventFilter(obj, event);
}

void SwitchButtonThumb::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(m_switchBtn->isEnabled() ? m_thumbColor : Qt::white);

    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    int s;
    QRectF r;

    if (Qt::Horizontal == m_switchBtn->orientation()) {
        s = height()-10;
        r = QRectF(5+m_offset, 0, height(), height());
    } else {
        s = width()-10;
        r = QRectF(5, 5+m_offset, s, s);
    }

    painter.drawEllipse(r);

    if (!m_switchBtn->isEnabled()) {
        brush.setColor(m_switchBtn->disabledColor());
        painter.setBrush(brush);
        painter.drawEllipse(r);
    }
}

void SwitchButtonThumb::updateOffset()
{
    const QSize s(Qt::Horizontal == m_switchBtn->orientation()
                  ? size() : size().transposed());
    m_offset = m_shift*static_cast<qreal>(s.width()-s.height());
    update();
}

SwitchButtonTrack::SwitchButtonTrack(SwitchButton *parent)
    : QWidget (parent)
    , m_switchBtn(parent)
{
    Q_ASSERT(parent);
    parent->installEventFilter(this);
}

SwitchButtonTrack::~SwitchButtonTrack()
{

}

void SwitchButtonTrack::setTrackColor(const QColor &color)
{
    m_trackColor = color;
    update();
}

bool SwitchButtonTrack::eventFilter(QObject *obj, QEvent *event)
{
    const QEvent::Type type = event->type();

    if (QEvent::Resize == type || QEvent::Move == type) {
        setGeometry(m_switchBtn->rect());
    }
    return QWidget::eventFilter(obj, event);
}

void SwitchButtonTrack::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush;
    if (m_switchBtn->isEnabled()) {
        brush.setColor(m_trackColor);
        painter.setOpacity(0.8);
    } else {
        brush.setColor(m_switchBtn->disabledColor());
        painter.setOpacity(0.6);
    }
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    if (Qt::Horizontal == m_switchBtn->orientation()) {
        const int h = height()/2;
        const QRect r(0, h/2, width(), h);
        painter.save();
        painter.setOpacity(1);
        painter.setBrush(QBrush(Qt::white));
        painter.drawRect(QRect(0, 0, width(), height()));
        painter.restore();
        painter.drawRoundedRect(r.adjusted(14, 0, -14, 0/*-4*/), h/2, h/2);
    } else {
        const int w = width()/2;
        const QRect r(w/2, 0, w, height());
        painter.drawRoundedRect(r.adjusted(4, 14, -4, -14), w/2, w/2);
    }
}
