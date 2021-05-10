#include "rippleoverlay.h"
#include "rippleanimation.h"
#include <QEvent>
#include <QMouseEvent>
#include <QPainterPath>
#include <QPainter>

RippleOverlay::RippleOverlay(QWidget *parent)
    : QWidget(parent)
    , m_clip(false)
{
    if (parent) {
        parent->installEventFilter(this);
    }
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_NoSystemBackground);
}

RippleOverlay::~RippleOverlay()
{

}

void RippleOverlay::addRipple(RippleAnimation *ripple)
{
    ripple->setOverlay(this);
    ripple->start();
    m_ripples.append(ripple);

    // 避免控件delete时动画还在运行，无法释放问题
    connect(this, &RippleOverlay::destroyed, ripple, &RippleAnimation::stop);
    connect(this, &RippleOverlay::destroyed, ripple, &RippleAnimation::destory);
}

void RippleOverlay::addRipple(const QPoint &center, qreal radius)
{
    auto ripple = new RippleAnimation(center);
    ripple->setRadiusEndValue(radius);
    addRipple(ripple);
}

void RippleOverlay::removeRipple(RippleAnimation *ripple)
{
    if (!ripple) {
        return ;
    }
    if (m_ripples.removeOne(ripple)) {
        delete ripple;
        update();
    }

}

void RippleOverlay::setClipping(bool enabled)
{
    m_clip = enabled;
    update();
}

void RippleOverlay::setClipPath(const QPainterPath &path)
{
    m_clipPath = path;
    update();
}

void RippleOverlay::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);

    if (m_clip) {
        painter.setClipPath(m_clipPath);
    }

    for (auto& ripple : m_ripples) {
        const qreal radius = ripple->radius();
        const QPointF center = ripple->center();
        painter.setOpacity(ripple->opacity());
        painter.setBrush(ripple->brush());
        painter.drawEllipse(center, radius, radius);
    }

}


bool RippleOverlay::event(QEvent *event)
{
    if (!parent()) {
        return QWidget::event(event);
    }

    switch (event->type()) {
    case QEvent::ParentChange:
        if (parent()) {
            parent()->installEventFilter(this);
            setGeometry(overlayGeometry());
        }
        break;

    case QEvent::ParentAboutToChange:
        if (parent()) {
            parent()->removeEventFilter(this);
        }
        break;
    default:
        break;
    }

    return QWidget::event(event);
}

bool RippleOverlay::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type()) {
    case QEvent::Move:
    case QEvent::Resize:
        setGeometry(overlayGeometry());
        break;
    case QEvent::MouseButtonPress: {
        auto mouseEvent = static_cast<QMouseEvent*>(event);
        QPoint pos = mouseEvent->pos();
        qreal redius = this->width() > this->height() ? this->width() / 2 : this->height() / 2;

        auto ripple = new RippleAnimation(pos, this, parent());
        ripple->setOpacity(0.5);
        ripple->setRadius(redius);
        ripple->setBrush(Qt::white);

        addRipple(ripple);
    }
        break;

    default:
        break;
    }

    return QWidget::eventFilter(watched, event);
}

QRect RippleOverlay::overlayGeometry() const
{

    auto widget = qobject_cast<QWidget*>(parent());
    if (!widget) {
        return QRect();
    }
    return widget->rect();
}
