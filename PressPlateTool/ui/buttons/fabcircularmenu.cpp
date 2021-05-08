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
    m_oneAngle = -(M_PI / 8.0 );
    m_multiAngle = -(M_PI / 8.0 * 3.0);
    m_distance = static_cast<qreal>(m_menuBtn->diameter()) * 2.5;

    setAttribute(Qt::WA_TransparentForMouseEvents);
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

    m_menuBtn->setIcon(QPixmap("/home/shijm/Documents/QtProject/ProtocolTools-Solution/PressPlateTool/resources/icons/down-arrow.png"));
    m_menuBtn->raise();
    m_addOneBtn = new QPushButton("one", parent);
    m_addMultiBtn = new QPushButton("multi", parent);

    updateCircularBtnGeometry();
    connect(m_addOneBtn, &QPushButton::clicked, this, &FabCircularMenu::notifyAddOne);
    connect(m_addMultiBtn, &QPushButton::clicked, this, &FabCircularMenu::notifyAddMulti);
}

FabCircularMenu::~FabCircularMenu()
{
    delete m_openState;
    delete m_closeState;
}

void FabCircularMenu::updateCircularBtnGeometry()
{

    qreal btn1x = parentWidget()->rect().x() + m_distance * qCos(m_angle + m_oneAngle);
    qreal btn1y = parentWidget()->rect().y() + parentWidget()->height() - m_distance * qSin(m_angle + m_oneAngle);
    auto rect = m_addOneBtn->rect();
    rect.moveCenter(QPoint(btn1x, btn1y));
    m_addOneBtn->setGeometry(rect);


    int btn2x = parentWidget()->rect().x() + m_distance * qCos(m_angle + m_multiAngle);
    int btn2y = parentWidget()->rect().y() + parentWidget()->height() - m_distance * qSin(m_angle + m_multiAngle);
    rect = m_addMultiBtn->rect();
    rect.moveCenter(QPoint(btn2x, btn2y));
    m_addMultiBtn->setGeometry(rect);
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
