#include "rippleanimation.h"
#include "rippleeffect.h"

Ui::RippleAnimation::RippleAnimation(const QPoint &center, RippleEffect *overlay, QObject *parent)
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

Ui::RippleAnimation::~RippleAnimation()
{
    delete m_opacityAnimation;
    delete m_radiusAnimation;

}
void Ui::RippleAnimation::setOpacity(const qreal &opacity)
{
    Q_ASSERT(m_overlay);
    if (qFuzzyCompare(m_opacity, opacity)) {
        return;
    }
    m_opacity = opacity;
    m_overlay->update();
}

void Ui::RippleAnimation::setRadius(const qreal &radius)
{
    Q_ASSERT(m_overlay);
    if (qFuzzyCompare(m_radius, radius)) {
        return;
    }
    m_radius = radius;
    m_overlay->update();
}

void Ui::RippleAnimation::setBrush(const QBrush &brush)
{
    Q_ASSERT(m_overlay);
    m_brush = brush;
    m_overlay->update();
}

void Ui::RippleAnimation::setCenter(const QPoint &center)
{
    Q_ASSERT(m_overlay);
    m_center = center;
    m_overlay->update();
}

void Ui::RippleAnimation::setOverlay(RippleEffect *overlay)
{
    m_overlay = overlay;
}

QPropertyAnimation *Ui::RippleAnimation::buildAnimation(const QString &property, const QEasingCurve &easing, int duration)
{
    auto animate = new QPropertyAnimation();
    animate->setTargetObject(this);
    animate->setPropertyName(property.toUtf8());
    animate->setEasingCurve(easing);
    animate->setDuration(duration);
    this->addAnimation(animate);
    return animate;
}

void Ui::RippleAnimation::init()
{
    setOpacityStartValue(0.5);
    setOpacityEndValue(0);
    setRadiusStartValue(0);
    setRadiusEndValue(200);

    m_brush.setColor(Qt::black);
    m_brush.setStyle(Qt::SolidPattern);

    connect(this, &RippleAnimation::finished, this, &RippleAnimation::destory);
}

void Ui::RippleAnimation::destory()
{
    Q_ASSERT(m_overlay);

    m_overlay->removeRipple(this);
}
