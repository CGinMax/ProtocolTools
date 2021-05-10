#include "rippleanimation.h"
#include "rippleoverlay.h"

RippleAnimation::RippleAnimation(const QPoint &center, RippleOverlay *overlay, QObject *parent)
    : QParallelAnimationGroup(parent)
    , m_opacity(0)
    , m_radius(0)
    , m_brush(QBrush())
    , m_center(center)
    , m_overlay(overlay)
    , m_opacityAnimation(buildAnimation("opacity"))
    , m_radiusAnimation(buildAnimation("radius"))
{
    init();
}

RippleAnimation::~RippleAnimation()
{
    delete m_opacityAnimation;
    delete m_radiusAnimation;

}
void RippleAnimation::setOpacity(const qreal &opacity)
{
    Q_ASSERT(m_overlay);
    if (qFuzzyCompare(m_opacity, opacity)) {
        return;
    }
    m_opacity = opacity;
    m_overlay->update();
}

void RippleAnimation::setRadius(const qreal &radius)
{
    Q_ASSERT(m_overlay);
    if (qFuzzyCompare(m_radius, radius)) {
        return;
    }
    m_radius = radius;
    m_overlay->update();
}

void RippleAnimation::setBrush(const QBrush &brush)
{
    Q_ASSERT(m_overlay);
    m_brush = brush;
    m_overlay->update();
}

void RippleAnimation::setCenter(const QPoint &center)
{
    Q_ASSERT(m_overlay);
    m_center = center;
    m_overlay->update();
}

void RippleAnimation::setOverlay(RippleOverlay *overlay)
{
    m_overlay = overlay;
}

QPropertyAnimation *RippleAnimation::buildAnimation(const QString &property, const QEasingCurve &easing, int duration)
{
    auto animate = new QPropertyAnimation();
    animate->setTargetObject(this);
    animate->setPropertyName(property.toUtf8());
    animate->setEasingCurve(easing);
    animate->setDuration(duration);
    this->addAnimation(animate);
    return animate;
}

void RippleAnimation::init()
{
    setOpacityStartValue(0.5);
    setOpacityEndValue(0);
    setRadiusStartValue(0);
    setRadiusEndValue(200);

    m_brush.setColor(Qt::black);
    m_brush.setStyle(Qt::SolidPattern);

    connect(this, &RippleAnimation::finished, this, &RippleAnimation::destory);
}

void RippleAnimation::destory()
{
    Q_ASSERT(m_overlay);

    m_overlay->removeRipple(this);
}
