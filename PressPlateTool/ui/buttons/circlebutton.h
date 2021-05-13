#ifndef CIRCLEBUTTON_H
#define CIRCLEBUTTON_H

#include <QWidget>
#include <QAbstractButton>
#include <QPropertyAnimation>
#include <QStateMachine>
#include <QState>
#include <QEventTransition>
#include <QGraphicsDropShadowEffect>

class RippleOverlay;

class CircleButton : public QAbstractButton
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)
public:
    explicit CircleButton(QWidget *parent = nullptr);
    ~CircleButton() override;

    QSize sizeHint() const override;

    void setShadowEnabled(bool enabled);

    void setHoverEnabled(bool enabled);

    qreal opacity() const;
    void setOpacity(qreal opacity);

    int iconSize() const;
    void setIconSize(int iconSize);

    int diameter() const;
    void setDiameter(int diameter);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &backgroundColor);

    QColor foregroundColor() const;
    void setForegroundColor(const QColor &foregroundColor);



protected:
    bool event(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    void updateRippleClipPath();

    void initShadowAnimation();
    void initHoverAnimation();
signals:

public slots:

protected:
    qreal m_opacity;
    int m_iconSize;
    int m_diameter;
    QColor m_backgroundColor;
    QColor m_foregroundColor;
    RippleOverlay* m_rippleOverly;

    bool m_hoveEnabled;
    QStateMachine* m_stateMachine;
    QState* m_normalState;
    QState* m_pressedState;
    QGraphicsDropShadowEffect* m_effect;

};

#endif // CIRCLEBUTTON_H
