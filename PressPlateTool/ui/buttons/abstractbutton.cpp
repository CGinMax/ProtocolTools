#include "abstractbutton.h"
#include "abstractbutton_p.h"

#include "rippleeffect.h"
#include "../base/theme.h"

Ui::AbstractButtonPrivate::AbstractButtonPrivate(AbstractButton *q)
    : q_ptr(q)
    , m_bgMode(Qt::OpaqueMode)
    , m_backgroundColor(Theme::instance()->primaryColor())
    , m_foregroundColor(Theme::instance()->textColor())
    , m_disabledColor(Theme::instance()->disabledColor())
    , m_disabledBackgroundColor(Theme::instance()->disabledColor())
    , m_rippleColor(Qt::gray)
    , m_borderColor(Qt::transparent)
    , m_opacity(1.0)
    , m_xradius(0)
    , m_yradius(0)
    , m_enabledBorder(false)
    , m_borderWidth(1)
{

}

Ui::AbstractButtonPrivate::~AbstractButtonPrivate()
{

}

void Ui::AbstractButtonPrivate::init()
{
    Q_Q(AbstractButton);
    m_rippleEffect = new RippleEffect(q);
}

Ui::AbstractButton::AbstractButton(QWidget *parent)
    : QAbstractButton(parent)
    , d_ptr(new AbstractButtonPrivate(this))
    , m_enabledAdaptiveColor(false)
{
    d_func()->init();
}

Ui::AbstractButton::~AbstractButton()
{

}

void Ui::AbstractButton::setAdaptiveColor(bool enabled)
{
    m_enabledAdaptiveColor = enabled;
}

bool Ui::AbstractButton::adaptiveColor() const
{
    return m_enabledAdaptiveColor;
}

Ui::AbstractButton *Ui::AbstractButton::setOpacity(qreal opacity)
{
    Q_D(AbstractButton);
    if (d->m_opacity == opacity) {
        return this;
    }

    d->m_opacity = opacity;
    update();
    emit opacityChanged();

    return this;
}

qreal Ui::AbstractButton::opacity() const
{
    Q_D(const AbstractButton);
    return d->m_opacity;
}

Ui::AbstractButton *Ui::AbstractButton::setBackgroundColor(const QColor &color)
{
    Q_D(AbstractButton);
    if (color == d->m_backgroundColor) {
        return this;
    }
    d->m_backgroundColor = color;
    if (m_enabledAdaptiveColor) {
        d->m_foregroundColor = Ui::reverseColor(color);
    }
    update();
    return this;
}

QColor Ui::AbstractButton::backgroundColor() const
{
    Q_D(const AbstractButton);
    return d->m_backgroundColor;
}

Ui::AbstractButton *Ui::AbstractButton::setForegroundColor(const QColor &color)
{
    Q_D(AbstractButton);
    if (color == d->m_foregroundColor) {
        return this;
    }
    d->m_foregroundColor = color;
    if (m_enabledAdaptiveColor) {
//        d->m_backgroundColor = Ui::reverseColor(color);
    }
    update();
    return this;
}

QColor Ui::AbstractButton::foregroundColor() const
{
    Q_D(const AbstractButton);
    return d->m_foregroundColor;
}

Ui::AbstractButton *Ui::AbstractButton::setDisabledColor(const QColor &color)
{
    Q_D(AbstractButton);
    if (color == d->m_disabledColor) {
        return this;
    }

    d->m_disabledColor = color;
    update();
    return this;
}

QColor Ui::AbstractButton::disabledColor()
{
    Q_D(const AbstractButton);
    return d->m_disabledColor;
}

Ui::AbstractButton *Ui::AbstractButton::setDisabledBgColor(const QColor &color)
{
    Q_D(AbstractButton);
    if (color == d->m_disabledBackgroundColor) {
        return this;
    }

    d->m_disabledBackgroundColor = color;
    update();
    return this;
}

QColor Ui::AbstractButton::diabledBgColor() const
{
    Q_D(const AbstractButton);
    return d->m_disabledBackgroundColor;
}

Ui::AbstractButton *Ui::AbstractButton::setBorderColor(const QColor &color)
{
    Q_D(AbstractButton);
    if (d->m_borderColor == color) {
        return this;
    }

    d->m_borderColor = color;
    update();
    return this;
}

QColor Ui::AbstractButton::borderColor() const
{
    Q_D(const AbstractButton);
    return d->m_borderColor;
}

Ui::AbstractButton *Ui::AbstractButton::setXRadius(int radius)
{
    Q_D(AbstractButton);
    d->m_xradius = radius;
    update();

    return this;
}

int Ui::AbstractButton::xradius() const
{
    Q_D(const AbstractButton);
    return d->m_xradius;
}

Ui::AbstractButton *Ui::AbstractButton::setYRadius(int radius)
{
    Q_D(AbstractButton);
    d->m_yradius = radius;
    update();

    return this;
}

int Ui::AbstractButton::yradius() const
{
    Q_D(const AbstractButton);
    return d->m_yradius;
}

Ui::AbstractButton *Ui::AbstractButton::setEnabledBorder(bool enabled)
{
    Q_D(AbstractButton);
    if (d->m_enabledBorder == enabled) {
        return this;
    }

    d->m_enabledBorder = enabled;
    update();
    return this;
}

bool Ui::AbstractButton::borderEnabled() const
{
    Q_D(const AbstractButton);
    return d->m_enabledBorder;
}

Ui::AbstractButton *Ui::AbstractButton::setBorderWidth(int width)
{
    Q_D(AbstractButton);
    d->m_borderWidth = width;
    update();
    return this;
}

int Ui::AbstractButton::borderWidth() const
{
    Q_D(const AbstractButton);
    return d->m_borderWidth;
}

Ui::AbstractButton *Ui::AbstractButton::setRippleStyle(Ui::RippleStyle style)
{
    Q_D(AbstractButton);
    if (d->m_rippleEffect->rippleStyle() == style) {
        return this;
    }

    d->m_rippleEffect->setRippleStyle(style);
    return this;
}

Ui::RippleStyle Ui::AbstractButton::rippleStyle() const
{
    Q_D(const AbstractButton);
    return d->m_rippleEffect->rippleStyle();
}

Ui::AbstractButton *Ui::AbstractButton::setClipPath(const QPainterPath &path)
{
    Q_D(AbstractButton);
    if (!d->m_rippleEffect->hasClipping()) {
        return this;
    }

    d->m_rippleEffect->setClipPath(path);
    return this;
}

Ui::AbstractButton::AbstractButton(Ui::AbstractButtonPrivate &d, QWidget *parent)
    : QAbstractButton (parent)
    , d_ptr(&d)
    , m_enabledAdaptiveColor(false)
{
    d_func()->init();
}
