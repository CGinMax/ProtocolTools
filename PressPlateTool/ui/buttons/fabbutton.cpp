#include "fabbutton.h"
#include "rippleoverlay.h"
#include <QEvent>
#include <QPainter>
#include <QPropertyAnimation>

FabButton::FabButton(QWidget *parent)
    : QAbstractButton(parent)
    , m_corner(Qt::BottomLeftCorner)
    , m_offsetX(20)
    , m_offsetY(20)
    , m_opacity(0.5)
    , m_iconSize(24)
    , m_diameter(56)
    , m_backgroundColor(QColor(Qt::lightGray))
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

    QEventTransition* transition = nullptr;
    transition = new QEventTransition(this, QEvent::HoverEnter);
    transition->setTargetState(m_hoverState);
    m_unhoverState->addTransition(transition);

    transition = new QEventTransition(this, QEvent::MouseButtonPress);
    transition->setTargetState(m_pressedState);
    m_hoverState->addTransition(transition);

//    transition = new QEventTransition(this, QEvent::MouseButtonDblClick);
//    transition->setTargetState(m_pressedState);
//    m_normalState->addTransition(transition);

    transition = new QEventTransition(this, QEvent::MouseButtonRelease);
    transition->setTargetState(m_hoverState);
    m_pressedState->addTransition(transition);

    transition = new QEventTransition(this, QEvent::HoverLeave);
    transition->setTargetState(m_unhoverState);
    m_hoverState->addTransition(transition);

    auto animation = new QPropertyAnimation(m_effect, "offset", this);
    animation->setDuration(100);
    m_stateMachine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(m_effect, "blurRadius", this);
    animation->setDuration(100);
    m_stateMachine->addDefaultAnimation(animation);

    animation = new QPropertyAnimation(this, "opacity", this);
    animation->setDuration(100);
    m_stateMachine->addDefaultAnimation(animation);

    m_stateMachine->setInitialState(m_unhoverState);
    m_stateMachine->start();

    setGeometry(fabGeometry());
    if (parentWidget()) {
        parentWidget()->installEventFilter(this);
    }

    m_rippleOverly = new RippleOverlay(this);

    m_rippleOverly->setClipping(true);
    QPainterPath path;
    QRect square = QRect(0, 0, m_diameter, m_diameter);
    square.moveCenter(rect().center());
    path.addEllipse(square);
    m_rippleOverly->setClipPath(path);

    setCheckable(true);
    setChecked(false);
}

FabButton::~FabButton()
{
    delete m_unhoverState;
    delete m_hoverState;
    delete m_pressedState;
    delete m_effect;
}

QRect FabButton::fabGeometry() const
{
    QWidget *parent = parentWidget();
    if (!parent) {
        return QRect();
    }

    const int s = diameter();
    // Qt::BottomRightCorner
    QRect rect(parent->width() - (m_offsetX + s), parent->height() - (m_offsetY + s), s, s);
    switch (m_corner)
    {
    case Qt::TopLeftCorner:
        rect = QRect(m_offsetX, m_offsetY, s, s);
        break;
    case Qt::TopRightCorner:
        rect = QRect(parent->width() - (m_offsetX + s), m_offsetY, s, s);
        break;
    case Qt::BottomLeftCorner:
        rect = QRect(m_offsetX, parent->height() - (m_offsetY + s), s, s);
        break;
    default:
        break;
    }
    return rect;

}


bool FabButton::event(QEvent *event)
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

    if (!parent()) {
        return QAbstractButton::event(event);
    }
    switch (event->type())
    {
    case QEvent::ParentChange:
    {
        parent()->installEventFilter(this);
        setGeometry(fabGeometry());
        break;
    }
    case QEvent::ParentAboutToChange:
    {
        parent()->removeEventFilter(this);
        break;
    }
    default:
        break;
    }
    return QAbstractButton::event(event);
}

qreal FabButton::opacity() const
{
    return m_opacity;
}

void FabButton::setOpacity(const qreal &opacity)
{
    m_opacity = opacity;
    update();
}


void FabButton::paintEvent(QPaintEvent *event)
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
    if (!isEnabled()) {
        icon.fillRect(pixmap.rect(), QColor(0xE0E0E0));
    }
//    icon.fillRect(pixmap.rect(), isEnabled() ? foregroundColor()
//                                             : disabledForegroundColor());
    painter.drawPixmap(iconGeometry, pixmap);

}

bool FabButton::eventFilter(QObject *obj, QEvent *event)
{
    const QEvent::Type type = event->type();
    if (type == QEvent::Move || type == QEvent::Resize) {
        setGeometry(fabGeometry());
    }

    return QAbstractButton::eventFilter(obj, event);
}

int FabButton::offsetY() const
{
    return m_offsetY;
}

void FabButton::setOffsetY(int y)
{
    m_offsetY = y;
    setGeometry(fabGeometry());
    update();
}

void FabButton::setOffset(int x, int y)
{
    m_offsetX = x;
    m_offsetY = y;
    setGeometry(fabGeometry());
    update();
}

void FabButton::setOffset(const QSize &size)
{
    setOffset(size.width(), size.height());
}

QSize FabButton::offset() const
{
    return QSize(m_offsetX, m_offsetY);
}

int FabButton::offsetX() const
{
    return m_offsetX;
}

void FabButton::setOffsetX(int x)
{
    m_offsetX = x;
    setGeometry(fabGeometry());
    update();
}

Qt::Corner FabButton::corner() const
{
    return m_corner;
}

void FabButton::setCorner(Qt::Corner corner)
{
    if (m_corner == corner) {
        return;
    }
    m_corner = corner;
    setGeometry(fabGeometry());
    update();
}

QColor FabButton::backgroundColor() const
{
    return m_backgroundColor;
}

void FabButton::setBackgroundColor(const QColor &backgroundColor)
{
    m_backgroundColor = backgroundColor;
    update();
}

int FabButton::diameter() const
{
    return m_diameter;
}

void FabButton::setDiameter(int diameter)
{
    m_diameter = diameter;
    QPainterPath path;
    QRect square = QRect(0, 0, m_diameter, m_diameter);
    square.moveCenter(rect().center());
    path.addEllipse(square);
    m_rippleOverly->setClipPath(path);
    update();
}

int FabButton::iconSize() const
{
    return m_iconSize;
}

void FabButton::setIconSize(int iconSize)
{
    m_iconSize = iconSize;
    update();
}


QSize FabButton::sizeHint() const
{
    return QSize(diameter(), diameter());
}
