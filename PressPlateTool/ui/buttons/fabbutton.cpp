#include "fabbutton.h"

FabButton::FabButton(QWidget *parent)
    : IconButton(parent)
    , m_corner(Qt::BottomRightCorner)
    , m_offsetX(8)
    , m_offsetY(8)
{
    if (parent != nullptr) {
        parent->installEventFilter(this);
    }
    setGeometry(fabGeometry());
    setCheckable(true);
    setChecked(false);
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


bool FabButton::event(QEvent *event)
{
    if (!parent()) {
        return IconButton::event(event);
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
    return IconButton::event(event);
}

bool FabButton::eventFilter(QObject *obj, QEvent *event)
{
    const QEvent::Type type = event->type();
    if (type == QEvent::Move || type == QEvent::Resize) {
        setGeometry(fabGeometry());
        updateRippleClipPath();
    }

    return IconButton::eventFilter(obj, event);
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
