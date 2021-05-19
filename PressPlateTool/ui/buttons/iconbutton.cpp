#include "iconbutton.h"
#include "iconbutton_p.h"
#include "rippleeffect.h"
#include <QEvent>
#include <QPainter>
#include <QPainterPath>

Ui::IconButtonPrivate::IconButtonPrivate(Ui::IconButton* q)
    : RaiseButtonPrivate (q)
    , m_enabledBackground(true)
    , m_opacity(1.0)
    , m_enabledHover(false)
{}

Ui::IconButtonPrivate::~IconButtonPrivate()
{}

void Ui::IconButtonPrivate::init()
{
    Q_Q(IconButton);
    m_shadowEffect->setEnabled(false);
    m_rippleEffect->setClipping(true);
    auto policy = q->sizePolicy();
    policy.setWidthForHeight(true);
    q->setSizePolicy(policy);
    q->resize(QSize(24, 24));
}

Ui::IconButton::IconButton(const QIcon &icon, QWidget *parent)
    : RaiseButton(*new IconButtonPrivate(this), icon, parent)
{
    d_func()->init();
    updateRippleClipPath();
}

Ui::IconButton::~IconButton()
{
}

QSize Ui::IconButton::sizeHint() const
{
    return {16 + iconSize().width(), 16 + iconSize().height()};
}

Ui::IconButton *Ui::IconButton::setOpacity(qreal opacity)
{
    Q_D(IconButton);
    d->m_opacity = opacity;
    update();
    return this;
}

qreal Ui::IconButton::opacity() const
{
    Q_D(const IconButton);
    return d->m_opacity;
}

Ui::IconButton *Ui::IconButton::setEnabledHover(bool enabled)
{
    Q_D(IconButton);
    if (d->m_enabledHover == enabled) {
        return this;
    }

    d->m_enabledHover = enabled;
    update();
    return this;
}

bool Ui::IconButton::enabledHover() const
{
    Q_D(const IconButton);
    return d->m_enabledHover;
}

Ui::IconButton *Ui::IconButton::setBackgroundEnabled(bool enabled)
{
    Q_D(IconButton);
    if (d->m_enabledBackground == enabled) {
        return this;
    }

    d->m_enabledBackground = enabled;
    update();
    return this;
}

bool Ui::IconButton::backgroundEnabled() const
{
    Q_D(const IconButton);
    return d->m_enabledBackground;
}

Ui::IconButton *Ui::IconButton::setIconColor(const QColor &color)
{
    return static_cast<IconButton*>(setForegroundColor(color));
}

QColor Ui::IconButton::iconColor() const
{
    return foregroundColor();
}

Ui::IconButton::IconButton(Ui::IconButtonPrivate &d, const QIcon &icon, QWidget *parent)
    : RaiseButton(d, icon, parent)
{
    d_func()->init();
    updateRippleClipPath();
}

bool Ui::IconButton::event(QEvent *event)
{
    Q_D(IconButton);
    if (d->m_enabledHover) {
        if (event->type() == QEvent::HoverEnter){
            setOpacity(1.0);
        } else if (event->type() == QEvent::HoverLeave && !isChecked()) {
            setOpacity(0.5);
        }
    }

    return QAbstractButton::event(event);
}


void Ui::IconButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    Q_D(IconButton);

    QRect square = QRect(0, 0, width(), height());
    square.moveCenter(rect().center());

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(Qt::NoPen);
    QBrush brush(Qt::SolidPattern);
    if (d->m_enabledBackground) {
        brush.setColor(backgroundColor());
        if (!isEnabled()) {
            brush.setColor(disabledColor());
        }
        if (d->m_enabledHover) {
            isChecked() ? painter.setOpacity(1.0): painter.setOpacity(opacity());
        }


    } else {
        brush.setColor(Qt::transparent);
        if (isChecked()) {
            brush.setColor(backgroundColor());
        }
    }
    painter.setBrush(brush);
    painter.drawRoundedRect(square, xradius(), yradius());


    QRect iconGeometry({0, 0}, iconSize());
    iconGeometry.moveCenter(square.center());
    drawIcon(&painter, iconGeometry);
}

