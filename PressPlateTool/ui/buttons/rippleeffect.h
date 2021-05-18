#ifndef RIPPLEEFFECT_H
#define RIPPLEEFFECT_H

#include <QWidget>
#include <QLinkedList>
#include <QPainterPath>
#include "../base/style.h"

namespace Ui {
class RippleAnimation;

class RippleEffect : public QWidget
{
    Q_OBJECT
public:
    explicit RippleEffect(QWidget *parent = nullptr);
    ~RippleEffect() override;
    void addRipple(RippleAnimation* ripple);
    void addRipple(const QPoint& center, qreal radius);

    void removeRipple(RippleAnimation* ripple);

    void setRippleStyle(RippleStyle style);
    inline RippleStyle rippleStyle() const;

    inline bool hasClipping() const;
    void setClipping(bool enabled);
    void setClipPath(const QPainterPath& path);
    inline QLinkedList<RippleAnimation*> ripples() const;
protected:
    void paintEvent(QPaintEvent *event) override;
    bool event(QEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

    QRect overlayGeometry() const;
signals:

public slots:

private:
    RippleStyle m_rippleStyle;
    bool m_clip;
    QPainterPath m_clipPath;
    QLinkedList<RippleAnimation*> m_ripples;
};
RippleStyle RippleEffect::rippleStyle() const
{
    return m_rippleStyle;
}

inline bool RippleEffect::hasClipping() const
{
    return m_clip;
}

inline QLinkedList<RippleAnimation*> RippleEffect::ripples() const
{
    return m_ripples;
}

}  // namespace Ui

#endif // RIPPLEEFFECT_H
