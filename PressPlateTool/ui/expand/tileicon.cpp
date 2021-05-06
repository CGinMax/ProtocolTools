#include "tileicon.h"
#include <QPixmap>
#include <QTransform>

TileIcon::TileIcon(QWidget *parent)
    : QLabel(parent)
    , m_rotation(0.0)
    , m_rotationAnimation(new QPropertyAnimation(this))
{
    m_rotationAnimation->setTargetObject(this);
    m_rotationAnimation->setPropertyName(QByteArray("rotation"));
    m_rotationAnimation->setDuration(150);
    m_rotationAnimation->setStartValue(0.0);
    m_rotationAnimation->setEndValue(90.0);
}

void TileIcon::setRotation(qreal angle)
{
    auto iconPixmap = this->pixmap();
    QTransform t;
    t.rotate(angle);
    iconPixmap->transformed(t);
    setPixmap(*iconPixmap);
}

qreal TileIcon::rotation() const
{
    return m_rotation;
}

void TileIcon::rotateIcon(bool rotated)
{
    QAbstractAnimation::Direction direction = QAbstractAnimation::Forward;
    if (!rotated) {
        direction = QAbstractAnimation::Backward;
    }
    m_rotationAnimation->setDirection(direction);
    m_rotationAnimation->start();
}
