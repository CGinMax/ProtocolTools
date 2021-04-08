#include "maintabbar.h"
#include <QMouseEvent>

MainTabBar::MainTabBar(QWidget *parent)
    : QTabBar(parent)
{

}

void MainTabBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        const auto tabIndex = tabAt(event->pos());
        emit tabAtIndexClicked(tabIndex);
        return;
    }
    QTabBar::mousePressEvent(event);
}
