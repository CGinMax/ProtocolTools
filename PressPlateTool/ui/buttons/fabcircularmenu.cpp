#include "fabcircularmenu.h"
#include <QEvent>
#include <QSignalTransition>
#include <QtMath>
#include <QApplication>
#include <QDebug>

FabCircularMenu::FabCircularMenu(QWidget *parent)
    : QWidget(parent)
    , m_angle(0.0)
    , m_distance(130)
    , m_menuBtn(new FabButton(parent))
    , m_stateMachine(new QStateMachine(this))
    , m_openState(new QState())
    , m_closeState(new QState())
{
    m_distance = static_cast<qreal>(m_menuBtn->diameter()) * 2.5;

    setMouseTracking(true);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_NoSystemBackground);
    m_stateMachine->addState(m_openState);
    m_stateMachine->addState(m_closeState);

    m_openState->assignProperty(this, "angle", M_PI_2);
    m_closeState->assignProperty(this, "angle", 0.0);

    auto transition = new QSignalTransition(m_menuBtn, &QAbstractButton::toggled, m_closeState);
    transition->setTargetState(m_openState);
    m_closeState->addTransition(transition);

    auto animation = new QPropertyAnimation(this);
    animation->setTargetObject(this);
    animation->setPropertyName(QByteArray("angle"));
    animation->setDuration(150);
    transition->addAnimation(animation);

    transition = new QSignalTransition(m_menuBtn, &QAbstractButton::toggled, m_openState);
    transition->setTargetState(m_closeState);
    m_openState->addTransition(transition);

    animation = new QPropertyAnimation(this);
    animation->setTargetObject(this);
    animation->setPropertyName(QByteArray("angle"));
    animation->setDuration(150);
    transition->addAnimation(animation);


    m_stateMachine->setInitialState(m_closeState);
    m_stateMachine->start();

    m_menuBtn->setIcon(QIcon(":/icons/fab-menu.png"));
    m_menuBtn->raise();
    updateCircularBtnGeometry();
}

FabCircularMenu::~FabCircularMenu()
{
    delete m_openState;
    delete m_closeState;
}

void FabCircularMenu::addButton(QAbstractButton *btn)
{
    if (m_btnList.count() > 4) {
        qDebug("Failed! It is more than 4 buttons");
        return ;
    }
    btn->setParent(parentWidget());
    m_btnList.append(btn);
    btn->raise();
    resetBtnsInitAngle();
}

void FabCircularMenu::insertButton(int index, QAbstractButton *btn)
{

    if (m_btnList.count() > 4) {
        qDebug("Failed! It is more than 4 buttons");
        return ;
    }
    btn->setParent(parentWidget());
    m_btnList.insert(index, btn);
    btn->raise();
    resetBtnsInitAngle();
}

qreal FabCircularMenu::angle() const
{
    return m_angle;
}

void FabCircularMenu::setAngle(qreal angle)
{
    m_angle = angle;
    updateCircularBtnGeometry();
}

void FabCircularMenu::updateCircularBtnGeometry()
{
    for (auto& btn : m_btnList) {
        qreal btnx = parentWidget()->rect().x() + m_distance * qCos(m_angle + m_initAngleMap.value(btn));
        qreal btny = parentWidget()->rect().y() + parentWidget()->height() - m_distance * qSin(m_angle + m_initAngleMap.value(btn));
        auto rect = btn->rect();
        rect.moveCenter(QPoint(btnx, btny));
        btn->setGeometry(rect);
    }
}

void FabCircularMenu::resetBtnsInitAngle()
{
    m_initAngleMap.clear();
    qreal apart = (m_distance - 8 - 8) / m_btnList.count();
//    qDebug() << "------------";
//    qDebug() << apart;
    for (int i = 0; i < m_btnList.count(); i++) {
        qreal btnDistance = 8 + (m_btnList.count() - i) * apart;
        m_initAngleMap.insert(m_btnList.at(i), -qAcos(btnDistance / m_distance));
//        qDebug() << "distance:" << btnDistance;
//        qDebug() << "angle:" << -qAcos(btnDistance / m_distance);
    }
}
