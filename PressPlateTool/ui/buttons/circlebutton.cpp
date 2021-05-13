#include "circlebutton.h"
#include "rippleoverlay.h"
#include <QEvent>
#include <QPainter>
#include <QPainterPath>

CircleButton::CircleButton(QWidget *parent)
    : QAbstractButton(parent)
    , m_opacity(1.0)
    , m_iconSize(24)
    , m_diameter(56)
    , m_backgroundColor(QColor(Qt::lightGray))
    , m_foregroundColor(QColor(Qt::white))
    , m_hoveEnabled(false)
    , m_stateMachine(new QStateMachine(this))
    , m_normalState(new QState())
    , m_pressedState(new QState())
    , m_effect(new QGraphicsDropShadowEffect(this))
{
    m_effect->setBlurRadius(7);
    m_effect->setOffset(QPointF(0, 2));
    m_effect->setColor(QColor(0, 0, 0, 105));
    setGraphicsEffect(m_effect);

    m_stateMachine->addState(m_normalState);
    m_stateMachine->addState(m_pressedState);

    m_normalState->assignProperty(m_effect, "offset", QPointF(0, 6));
    m_normalState->assignProperty(m_effect, "blurRadius", 16);

    m_pressedState->assignProperty(m_effect, "offset", QPointF(0, 11));
    m_pressedState->assignProperty(m_effect, "blurRadius", 28);

    QEventTransition* transition = nullptr;
    transition = new QEventTransition(this, QEvent::MouseButtonPress);
    transition->setTargetState(m_pressedState);
    m_normalState->addTransition(transition);

    transition = new QEventTransition(this, QEvent::MouseButtonRelease);
    transition->setTargetState(m_normalState);
    m_pressedState->addTransition(transition);

    auto animation = new QPropertyAnimation(m_effect, "offset", this);
    animation->setDuration(100);
    m_stateMachine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(m_effect, "blurRadius", this);
    animation->setDuration(100);
    m_stateMachine->addDefaultAnimation(animation);

    m_stateMachine->setInitialState(m_normalState);
    m_stateMachine->start();

    if (!m_hoveEnabled) {
        m_effect->setEnabled(false);
    }
//    initShadowAnimation();
//    initHoverAnimation();

    m_rippleOverly = new RippleOverlay(this);

    m_rippleOverly->setClipping(true);
    updateRippleClipPath();

    resize(diameter() +39 , diameter() + 39);
}

CircleButton::~CircleButton()
{
    delete m_normalState;
    delete m_pressedState;
    delete m_effect;
}

QSize CircleButton::sizeHint() const
{
    return QSize(diameter() +39 , diameter() + 39);
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
    m_hoveEnabled = enabled;
}

qreal CircleButton::opacity() const
{
    return m_opacity;
}

void CircleButton::setOpacity(qreal opacity)
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

    resize(diameter, diameter);
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
    if (m_hoveEnabled) {
        if (event->type() == QEvent::HoverEnter || (isCheckable() && isChecked())){
            setOpacity(1.0);
            m_effect->setEnabled(true);
        } else if (event->type() == QEvent::HoverLeave) {
            setOpacity(0.5);
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

void CircleButton::initShadowAnimation()
{

}

void CircleButton::initHoverAnimation()
{

}
