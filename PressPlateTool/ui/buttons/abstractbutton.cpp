#include "abstractbutton.h"
#include "abstractbutton_p.h"

#include "rippleeffect.h"

Ui::AbstractButtonPrivate::AbstractButtonPrivate(AbstractButton *q)
    : q_ptr(q)
    , m_rippleEffect(new RippleEffect(q))
    , m_rippleStyle(Ui::RippleStyle::PositionedRipple)
    , m_bgMode(Qt::OpaqueMode)
    , m_backgroundColor(Qt::blue)
    , m_foregroundColor(Qt::white)
    , m_disabledColor(Qt::gray)
    , m_disabledBackgroundColor(Qt::darkGray)
    , m_rippleColor(Qt::gray)
{

}

Ui::AbstractButtonPrivate::~AbstractButtonPrivate()
{

}

void Ui::AbstractButtonPrivate::init()
{

}

Ui::AbstractButton::AbstractButton(QWidget *parent)
    : QAbstractButton(parent)
    , d_ptr(new AbstractButtonPrivate(this))
{

}

Ui::AbstractButton::~AbstractButton()
{

}

void Ui::AbstractButton::setOpacity(qreal opacity)
{
    Q_D(AbstractButton);
    if (d->m_opacity == opacity) {
        return ;
    }

    d->m_opacity = opacity;
    update();
    emit opacityChanged();
}

qreal Ui::AbstractButton::opacity() const
{
    Q_D(const AbstractButton);
    return d->m_opacity;
}

