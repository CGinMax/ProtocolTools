#include "fakeclosebutton.h"

FakeCloseButton::FakeCloseButton(QWidget *parent) : QAbstractButton(parent)
{
    setFocusPolicy(Qt::NoFocus);
#ifndef QT_NO_CURSOR
    setCursor(Qt::ArrowCursor);
#endif
#ifndef QT_NO_TOOLTIP
    setToolTip(tr("关闭标签页"));
#endif
    resize(sizeHint());
}

void FakeCloseButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
}
