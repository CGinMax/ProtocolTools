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
    void addButton(QAbstractButton* btn);

    void insertButton(int index, QAbstractButton* btn);

    void setChecked(bool checked);

    qreal angle() const;
    void setAngle(qreal angle);

private:
    void updateCircularBtnGeometry();
    void resetBtnsInitAngle();
    bool eventFilter(QObject *watched, QEvent *event) override;

signals:

public slots:

private:
    qreal m_angle;
    qreal m_distance;
    FabButton* m_menuBtn;
    QStateMachine* m_stateMachine;
    QState* m_openState;
    QState* m_closeState;
    QMap<QAbstractButton*, qreal> m_initAngleMap;
    QList<QAbstractButton*> m_btnList;

};

#endif // FABCIRCULARMENU_H
