#include "realclosebutton.h"
#include <QStyle>
#include <QPainter>
#include <QStyleOption>

RealCloseButton::RealCloseButton(QWidget *parent)
    : QAbstractButton(parent)
{
    setFocusPolicy(Qt::NoFocus);
#ifndef QT_NO_CURSOR
    setCursor(Qt::ArrowCursor);
#endif
#ifndef QT_NO_TOOLTIP
    setToolTip(tr("Close Tab"));
#endif
    resize(sizeHint());
}

QSize RealCloseButton::sizeHint() const
{
    ensurePolished();
    int width = style()->pixelMetric(QStyle::PM_TabCloseIndicatorWidth, nullptr, this);
    int height = style()->pixelMetric(QStyle::PM_TabCloseIndicatorHeight, nullptr, this);
    return {width, height};
}

void RealCloseButton::enterEvent(QEvent *event)
{
    if (isEnabled()) {
        update();
    }
    QAbstractButton::enterEvent(event);
}

void RealCloseButton::leaveEvent(QEvent *event)
{
    if (isEnabled()) {
        update();
    }
    QAbstractButton::leaveEvent(event);
}

void RealCloseButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    QStyleOption option;
    option.init(this);
    option.state |= QStyle::State_AutoRaise;
    if (isEnabled() && underMouse() && !isChecked() && !isDown()) {
        option.state |= QStyle::State_Raised;
    }
    if (isChecked()) {
        option.state |= QStyle::State_On;
    }
    if (isDown()) {
        option.state |= QStyle::State_Sunken;
    }
    if (auto tabbar = qobject_cast<QTabBar*>(parent())) {
        int index = tabbar->currentIndex();
        QTabBar::ButtonPosition position =
                static_cast<QTabBar::ButtonPosition>(style()->styleHint(QStyle::SH_TabBar_CloseButtonPosition, nullptr, tabbar));

        if (tabbar->tabButton(index, position) == this) {
            option.state |= QStyle::State_Selected;
        }
    }

    style()->drawPrimitive(QStyle::PE_IndicatorTabClose, &option, &painter, this);
}
