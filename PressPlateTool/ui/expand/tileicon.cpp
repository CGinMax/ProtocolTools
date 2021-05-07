#include "tileicon.h"
#include <QPixmap>
#include <QTransform>

TileIcon::TileIcon(const QPixmap &pixmap, QWidget *parent)
    : QLabel(parent)
    , m_rotation(0.0)
    , m_rotationAnimation(new QPropertyAnimation(this))
    , m_pixmap(pixmap)
{
    QTransform t;
    t.rotate(-90);
    setPixmap(m_pixmap.transformed(t));

    m_rotationAnimation->setTargetObject(this);
    m_rotationAnimation->setPropertyName(QByteArray("rotation"));
    m_rotationAnimation->setDuration(150);
    m_rotationAnimation->setStartValue(-90.0);
    m_rotationAnimation->setEndValue(0.0);
}

void TileIcon::setRotation(qreal angle)
{
//    QTransform t;
//    t.rotate(angle);
//    setPixmap(m_pixmap.transformed(t));
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
