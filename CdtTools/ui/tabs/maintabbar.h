#ifndef MAINTABBAR_H
#define MAINTABBAR_H

#include <QTabBar>

class MainTabBar : public QTabBar
{
    Q_OBJECT
public:
    explicit MainTabBar(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
signals:
    void tabAtIndexClicked(int index);

public slots:
};

#endif // MAINTABBAR_H
