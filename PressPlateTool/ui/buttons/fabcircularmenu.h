#ifndef FABCIRCULARMENU_H
#define FABCIRCULARMENU_H

#include <QWidget>
#include <QPropertyAnimation>
#include "fabbutton.h"
#include <QPushButton>

class FabCircularMenu : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal angle WRITE setAngle READ angle)
public:
    explicit FabCircularMenu(QWidget *parent);
    ~FabCircularMenu() override;


    void updateCircularBtnGeometry();

    qreal angle() const;
    void setAngle(qreal angle);

signals:
    void notifyAddOne();
    void notifyAddMulti();

public slots:

private:
    qreal m_angle;
    qreal m_distance;
    FabButton* m_menuBtn;
    qreal m_oneAngle;
    qreal m_multiAngle;
    QPushButton* m_addOneBtn;
    QPushButton* m_addMultiBtn;
    QStateMachine* m_stateMachine;
    QState* m_openState;
    QState* m_closeState;
//    QList<QAbstractButton*> m_btnList;
};

#endif // FABCIRCULARMENU_H
