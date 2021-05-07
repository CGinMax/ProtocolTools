#ifndef TILEICON_H
#define TILEICON_H

#include <QLabel>
#include <QPropertyAnimation>

class TileIcon : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation WRITE setRotation READ rotation)
public:
    explicit TileIcon(const QPixmap& pixmap, QWidget *parent = nullptr);

    void setRotation(qreal angle);
    qreal rotation() const;

signals:

public slots:
    void rotateIcon(bool rotated);

private:
    qreal m_rotation;
    QPropertyAnimation* m_rotationAnimation;
    QPixmap m_pixmap;
};

#endif // TILEICON_H
