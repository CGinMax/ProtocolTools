#ifndef RIPPLEOVERLAY_H
#define RIPPLEOVERLAY_H

#include <QWidget>
#include <QLinkedList>

class RippleAnimation;

class RippleOverlay : public QWidget
{
    Q_OBJECT
public:
    explicit RippleOverlay(QWidget *parent = nullptr);
    ~RippleOverlay() override;
    void addRipple(RippleAnimation* ripple);
    void addRipple(const QPoint& center, qreal radius);

    void removeRipple(RippleAnimation* ripple);

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
    bool m_clip;
    QPainterPath m_clipPath;
    QLinkedList<RippleAnimation*> m_ripples;
};
inline bool RippleOverlay::hasClipping() const
{
    return m_clip;
}

inline QLinkedList<RippleAnimation*> RippleOverlay::ripples() const
{
    return m_ripples;
}

#endif // RIPPLEOVERLAY_H
