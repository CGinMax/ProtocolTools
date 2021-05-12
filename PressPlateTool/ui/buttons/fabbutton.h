#ifndef FABBUTTON_H
#define FABBUTTON_H

#include <QWidget>
#include <QAbstractButton>
#include <QStateMachine>
#include <QState>
#include <QEventTransition>
#include <QGraphicsDropShadowEffect>

class RippleOverlay;

class FabButton : public QAbstractButton
{
    Q_OBJECT
    Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)
public:
    explicit FabButton(QWidget *parent = nullptr);
    ~FabButton() override;

    QSize sizeHint() const override;

    void setShadowEnabled(bool enabled);

    void setHoverEnabled(bool enabled);

    qreal opacity() const;
    void setOpacity(const qreal &opacity);

    int iconSize() const;
    void setIconSize(int iconSize);

    int diameter() const;
    void setDiameter(int diameter);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &backgroundColor);

    QColor foregroundColor() const;
    void setForegroundColor(const QColor &foregroundColor);

    Qt::Corner corner() const;
    void setCorner(Qt::Corner corner);

    int offsetX() const;
    void setOffsetX(int x);

    int offsetY() const;
    void setOffsetY(int y);

    void setOffset(int x, int y);
    void setOffset(const QSize& size);
    QSize offset() const;

protected:
    bool event(QEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    QRect fabGeometry() const;
    void updateRippleClipPath();
signals:

public slots:

private:
    Qt::Corner m_corner;
    int m_offsetX;
    int m_offsetY;

    qreal m_opacity;
    int m_iconSize;
    int m_diameter;
    QColor m_backgroundColor;
    QColor m_foregroundColor;
    RippleOverlay* m_rippleOverly;

    bool m_hoveEnabled;
    QStateMachine* m_stateMachine;
    QState* m_unhoverState;
    QState* m_hoverState;
    QState* m_pressedState;
    QEventTransition* m_hoverTransition;
    QEventTransition* m_unhoverTransition;
    QGraphicsDropShadowEffect* m_effect;

};

#endif // FABBUTTON_H
