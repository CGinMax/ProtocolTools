#ifndef RIPPLEANIMATION_H
#define RIPPLEANIMATION_H

#include <QColor>
#include <QPoint>
#include <QBrush>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

class RippleOverlay;

class RippleAnimation : public QParallelAnimationGroup
{
    Q_OBJECT

    Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity NOTIFY opacityChanged)
    Q_PROPERTY(qreal radius WRITE setRadius READ radius NOTIFY radiusChanged)
public:
    explicit RippleAnimation(const QPoint& center, RippleOverlay* overlay = nullptr, QObject* parent = nullptr);
    ~RippleAnimation() override;

    inline qreal opacity() const;
    void setOpacity(const qreal &opacity);

    inline qreal radius() const;
    void setRadius(const qreal &radius);

    inline QBrush brush() const;
    void setBrush(const QBrush& brush);

    inline QPoint center() const;
    void setCenter(const QPoint& center);

    void setOverlay(RippleOverlay* overlay);

    inline QPropertyAnimation* opacityAnimation() const;
    inline QPropertyAnimation* radiusAnimation() const;

    inline void setOpacityStartValue(qreal value);
    inline void setOpacityEndValue(qreal value);
    inline void setRadiusStartValue(qreal value);
    inline void setRadiusEndValue(qreal value);
    inline void setDuration(int msec);

private:
    QPropertyAnimation* buildAnimation(const QString& property
                                       , const QEasingCurve &easing = QEasingCurve::OutCurve
                                       , int duration = 800);


private:
    void init();
signals:
    void opacityChanged(qreal opacity);

    void radiusChanged(qreal radius);
public slots:
    void destory();


private:
    qreal m_opacity;
    qreal m_radius;
    QBrush m_brush;
    QPoint m_center;
    RippleOverlay* m_overlay;
    QPropertyAnimation* const m_opacityAnimation;
    QPropertyAnimation* const m_radiusAnimation;
};
inline qreal RippleAnimation::opacity() const
{
    return m_opacity;
}

inline qreal RippleAnimation::radius() const
{
    return m_radius;
}

inline QBrush RippleAnimation::brush() const
{
    return m_brush;
}

inline QPoint RippleAnimation::center() const
{
    return m_center;
}

inline QPropertyAnimation* RippleAnimation::opacityAnimation() const
{
    return m_opacityAnimation;
}

inline QPropertyAnimation* RippleAnimation::radiusAnimation() const
{
    return m_radiusAnimation;
}

inline void RippleAnimation::setOpacityStartValue(qreal value)
{
    m_opacityAnimation->setStartValue(value);
}


inline void RippleAnimation::setOpacityEndValue(qreal value)
{
    m_opacityAnimation->setEndValue(value);
}

inline void RippleAnimation::setRadiusStartValue(qreal value)
{
    m_radiusAnimation->setStartValue(value);
}

inline void RippleAnimation::setRadiusEndValue(qreal value)
{
    m_radiusAnimation->setEndValue(value);
}

inline void RippleAnimation::setDuration(int msec)
{
    m_opacityAnimation->setDuration(msec);
}

#endif // RIPPLEANIMATION_H
