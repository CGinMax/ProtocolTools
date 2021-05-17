#include "iconbutton.h"
#include "rippleoverlay.h"
#include <QEvent>
#include <QPainter>
#include <QPainterPath>

IconButton::IconButton(QWidget *parent)
    : QAbstractButton(parent)
    , m_opacity(1.0)
    , m_iconSize(24)
    , m_diameter(56)
    , m_backgroundColor(QColor(Qt::lightGray))
    , m_foregroundColor(QColor(Qt::white))
    , m_hoveEnabled(false)
{

    m_rippleOverly = new Ui::RippleOverlay(this);

    m_rippleOverly->setClipping(true);
    updateRippleClipPath();
}

IconButton::~IconButton()
{
}

QSize IconButton::sizeHint() const
{
    return QSize(diameter() , diameter());
}

void IconButton::setHoverEnabled(bool enabled)
{
    if (m_hoveEnabled == enabled) {
        return ;
    }
    m_hoveEnabled = enabled;
}

qreal IconButton::opacity() const
{
    return m_opacity;
}

void IconButton::setOpacity(qreal opacity)
{
    m_opacity = opacity;
    update();
}

int IconButton::iconSize() const
{
    return m_iconSize;
}

void IconButton::setIconSize(int iconSize)
{
    m_iconSize = iconSize;
    update();
}

int IconButton::diameter() const
{
    return m_diameter;
}

void IconButton::setDiameter(int diameter)
{
    m_diameter = diameter;

    resize(diameter, diameter);
    updateRippleClipPath();
    update();
}

QColor IconButton::backgroundColor() const
{
    return m_backgroundColor;
}

void IconButton::setBackgroundColor(const QColor &backgroundColor)
{
    m_backgroundColor = backgroundColor;
    update();
}

QColor IconButton::foregroundColor() const
{
    return m_foregroundColor;
}

void IconButton::setForegroundColor(const QColor &foregroundColor)
{
    m_foregroundColor = foregroundColor;
}

bool IconButton::event(QEvent *event)
{
    if (m_hoveEnabled) {
        if (event->type() == QEvent::HoverEnter){
            setOpacity(1.0);
        } else if (event->type() == QEvent::HoverLeave && !isChecked()) {
            setOpacity(0.5);
        }
    }

    return QAbstractButton::event(event);
}


void IconButton::paintEvent(QPaintEvent *event)
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
    painter.drawRoundedRect(square, diameter(), diameter());

    QRect iconGeometry(0, 0, m_iconSize, m_iconSize);
    iconGeometry.moveCenter(square.center());

    QPixmap pixmap = icon().pixmap(QSize(m_iconSize, m_iconSize));
    QPainter icon(&pixmap);
    icon.setCompositionMode(QPainter::CompositionMode_SourceIn);

    icon.fillRect(pixmap.rect(), isEnabled() ? foregroundColor()
                                             : QColor(0xE0E0E0));
    painter.drawPixmap(iconGeometry, pixmap);

}

void IconButton::updateRippleClipPath()
{
    QPainterPath path;
    QRect square = QRect(0, 0, m_diameter, m_diameter);
    square.moveCenter(rect().center());
    path.addEllipse(square);
    m_rippleOverly->setClipPath(path);
}
