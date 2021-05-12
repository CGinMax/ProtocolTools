#include "circlebutton.h"
#include "rippleoverlay.h"
#include <QEvent>
#include <QPainter>

CircleButton::CircleButton(QWidget *parent)
    : QAbstractButton(parent)
    , m_opacity(0.5)
    , m_iconSize(24)
    , m_diameter(56)
    , m_backgroundColor(QColor(Qt::lightGray))
    , m_foregroundColor(QColor(Qt::white))
    , m_hoveEnabled(false)
    , m_stateMachine(new QStateMachine(this))
    , m_unhoverState(new QState())
    , m_hoverState(new QState())
    , m_pressedState(new QState())
    , m_effect(new QGraphicsDropShadowEffect(this))
{
    m_effect->setBlurRadius(7);
    m_effect->setOffset(QPointF(0, 2));
    m_effect->setColor(QColor(0, 0, 0, 105));
    setGraphicsEffect(m_effect);

    m_stateMachine->addState(m_unhoverState);
    m_stateMachine->addState(m_hoverState);
    m_stateMachine->addState(m_pressedState);

    m_unhoverState->assignProperty(m_effect, "offset", QPointF(0, 0));
    m_unhoverState->assignProperty(m_effect, "blurRadius", 0);
    m_unhoverState->assignProperty(this, "opacity", m_opacity);

    m_hoverState->assignProperty(m_effect, "offset", QPointF(0, 6));
    m_hoverState->assignProperty(m_effect, "blurRadius", 16);
    m_hoverState->assignProperty(this, "opacity", 1.0);

    m_pressedState->assignProperty(m_effect, "offset", QPointF(0, 11));
    m_pressedState->assignProperty(m_effect, "blurRadius", 28);

    m_hoverTransition = new QEventTransition(this, QEvent::HoverEnter);
    m_hoverTransition->setTargetState(m_hoverState);

    m_unhoverTransition = new QEventTransition(this, QEvent::HoverLeave);
    m_unhoverTransition->setTargetState(m_unhoverState);

    m_unhoverAnimation = new QPropertyAnimation(this, "opacity", this);
    m_unhoverAnimation->setDuration(100);

    m_hoverAnimation = new QPropertyAnimation(this, "opacity", this);
    m_hoverAnimation->setDuration(100);

    if (m_hoveEnabled) {
        m_unhoverState->addTransition(m_hoverTransition);
        m_hoverTransition->addAnimation(m_hoverAnimation);
        m_hoverState->addTransition(m_unhoverTransition);
        m_unhoverTransition->addAnimation(m_unhoverAnimation);
    }

    QEventTransition* transition = nullptr;
    transition = new QEventTransition(this, QEvent::MouseButtonPress);
    transition->setTargetState(m_pressedState);
    m_hoverState->addTransition(transition);

    transition = new QEventTransition(this, QEvent::MouseButtonRelease);
    transition->setTargetState(m_hoverState);
    m_pressedState->addTransition(transition);

    auto animation = new QPropertyAnimation(m_effect, "offset", this);
    animation->setDuration(100);
    m_stateMachine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(m_effect, "blurRadius", this);
    animation->setDuration(100);
    m_stateMachine->addDefaultAnimation(animation);


    m_stateMachine->setInitialState(m_hoveEnabled ? m_unhoverState : m_hoverState);
    m_stateMachine->start();

    m_rippleOverly = new RippleOverlay(this);

    m_rippleOverly->setClipping(true);
    updateRippleClipPath();

}

CircleButton::~CircleButton()
{
    delete m_unhoverState;
    delete m_hoverState;
    delete m_pressedState;
    delete m_effect;
}

QSize CircleButton::sizeHint() const
{
    return QSize(diameter(), diameter());
}

void CircleButton::setShadowEnabled(bool enabled)
{
    enabled ? m_stateMachine->start() : m_stateMachine->stop();
    m_effect->setEnabled(enabled);
}

void CircleButton::setHoverEnabled(bool enabled)
{
    if (m_hoveEnabled == enabled) {
        return ;
    }
    m_stateMachine->stop();
    if (enabled) {
        m_unhoverState->addTransition(m_hoverTransition);
        m_hoverTransition->addAnimation(m_hoverAnimation);
        m_hoverState->addTransition(m_unhoverTransition);
        m_unhoverTransition->addAnimation(m_unhoverAnimation);
        m_stateMachine->setInitialState(m_unhoverState);
    }
    else {
        m_hoverTransition->removeAnimation(m_hoverAnimation);
        m_unhoverState->removeTransition(m_hoverTransition);
        m_unhoverTransition->removeAnimation(m_unhoverAnimation);
        m_hoverState->removeTransition(m_unhoverTransition);
        m_stateMachine->setInitialState(m_hoverState);
    }
    m_stateMachine->start();
}


qreal CircleButton::opacity() const
{
    return m_opacity;
}

void CircleButton::setOpacity(const qreal &opacity)
{
    m_opacity = opacity;
    update();
}

int CircleButton::iconSize() const
{
    return m_iconSize;
}

void CircleButton::setIconSize(int iconSize)
{
    m_iconSize = iconSize;
    update();
}

int CircleButton::diameter() const
{
    return m_diameter;
}

void CircleButton::setDiameter(int diameter)
{
    m_diameter = diameter;
    updateRippleClipPath();
    update();
}

QColor CircleButton::backgroundColor() const
{
    return m_backgroundColor;
}

void CircleButton::setBackgroundColor(const QColor &backgroundColor)
{
    m_backgroundColor = backgroundColor;
    update();
}

QColor CircleButton::foregroundColor() const
{
    return m_foregroundColor;
}

void CircleButton::setForegroundColor(const QColor &foregroundColor)
{
    m_foregroundColor = foregroundColor;
}

bool CircleButton::event(QEvent *event)
{
    if (event->type() == QEvent::EnabledChange) {
        if (isEnabled()) {
            m_stateMachine->start();
            m_effect->setEnabled(true);
        } else {
            m_stateMachine->stop();
            m_effect->setEnabled(false);
        }
    }
    return QAbstractButton::event(event);
}


void CircleButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QRect square = QRect(0, 0, m_diameter, m_diameter);
    square.moveCenter(rect().center());

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QBrush brush(m_backgroundColor);
    brush.setStyle(Qt::SolidPattern);
    if (isEnabled()) {
        brush.setColor(m_backgroundColor);
    } else {
        brush.setColor(QColor(0xE0E0E0));// disable color
    }

    isChecked() ? painter.setOpacity(1.0): painter.setOpacity(m_opacity);

    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(square);

    QRect iconGeometry(0, 0, m_iconSize, m_iconSize);
    iconGeometry.moveCenter(square.center());

    QPixmap pixmap = icon().pixmap(QSize(m_iconSize, m_iconSize));
    QPainter icon(&pixmap);
    icon.setCompositionMode(QPainter::CompositionMode_SourceIn);

    icon.fillRect(pixmap.rect(), isEnabled() ? foregroundColor()
                                             : QColor(0xE0E0E0));
    painter.drawPixmap(iconGeometry, pixmap);

}


void CircleButton::updateRippleClipPath()
{
    QPainterPath path;
    QRect square = QRect(0, 0, m_diameter, m_diameter);
    square.moveCenter(rect().center());
    path.addEllipse(square);
    m_rippleOverly->setClipPath(path);
}
