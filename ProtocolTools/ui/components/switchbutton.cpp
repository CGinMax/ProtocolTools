#include "switchbutton.h"
#include "switchbutton_p.h"
#include <QtWidgets/QApplication>
#include <QStateMachine>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include "switchbutton_internal.h"

SwitchButtonPrivate::SwitchButtonPrivate(SwitchButton* q)
    : q_ptr(q)
{}

SwitchButtonPrivate::~SwitchButtonPrivate()
{}

void SwitchButtonPrivate::init()
{
    Q_Q(SwitchButton);
    q->setCheckable(true);
    q->setChecked(false);
    q->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    track = new SwitchButtonTrack(q);
    thumb = new SwitchButtonThumb(q);
    stateMachine = new QStateMachine(q);
    offState = new QState();
    onState = new QState();
    orientation = Qt::Horizontal;
    disabledColor = QColor(Qt::gray);
    activeColor = QColor(Qt::darkGreen);
    inactiveColor = QColor(Qt::darkRed);
    trackColor = QColor(Qt::darkRed);

    stateMachine->addState(offState);
    stateMachine->addState(onState);
    stateMachine->setInitialState(offState);

    offState->assignProperty(thumb, "shift", 0);
    onState->assignProperty(thumb, "shift", 1);

    QSignalTransition* transition;
    QPropertyAnimation* animation;

    // on animation transition
    transition = new QSignalTransition(q, &QAbstractButton::toggled);
    transition->setTargetState(onState);
    offState->addTransition(transition);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("shift");
    animation->setTargetObject(thumb);
    animation->setDuration(200);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("trackColor");
    animation->setTargetObject(track);
    animation->setDuration(150);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("thumbColor");
    animation->setTargetObject(thumb);
    animation->setDuration(150);
    transition->addAnimation(animation);

    // off
    transition = new QSignalTransition(q, &QAbstractButton::toggled);
    transition->setTargetState(offState);
    onState->addTransition(transition);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("shift");
    animation->setTargetObject(thumb);
    animation->setDuration(200);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("trackColor");
    animation->setTargetObject(track);
    animation->setDuration(150);
    transition->addAnimation(animation);

    animation = new QPropertyAnimation(q);
    animation->setPropertyName("thumbColor");
    animation->setTargetObject(thumb);
    animation->setDuration(150);
    transition->addAnimation(animation);


    setupProperties();
    stateMachine->start();
}

void SwitchButtonPrivate::setupProperties()
{
    Q_Q(SwitchButton);

    if (q->isEnabled()) {
        const qreal shift = thumb->shift();
        if (qFuzzyCompare(shift, 1)) {
            thumb->setThumbColor(q->activeColor());
            track->setTrackColor(q->activeColor().lighter(110));
        } else if (qFuzzyCompare(1+shift, 1)) {
            thumb->setThumbColor(q->inactiveColor());
            track->setTrackColor(q->trackColor());
        }
    }

    offState->assignProperty(track, "trackColor", q->trackColor().lighter(110));
    onState->assignProperty(track, "trackColor", q->activeColor().lighter(110));

    offState->assignProperty(thumb, "thumbColor", q->inactiveColor());
    onState->assignProperty(thumb, "thumbColor", q->activeColor());

    q->update();
}

SwitchButton::SwitchButton(QWidget *parent)
    : QAbstractButton(parent)
    , d_ptr(new SwitchButtonPrivate(this))
{
    d_ptr->init();
}

SwitchButton::~SwitchButton()
{

}

void SwitchButton::setDisabledColor(const QColor &color)
{
    Q_D(SwitchButton);

    d->disabledColor = color;
    d->setupProperties();
}

QColor SwitchButton::disabledColor() const
{
    Q_D(const SwitchButton);
    return d->disabledColor;
}

void SwitchButton::setActiveColor(const QColor &color)
{
    Q_D(SwitchButton);
    d->activeColor = color;
    d->setupProperties();
}

QColor SwitchButton::activeColor() const
{
    Q_D(const SwitchButton);
    return d->activeColor;
}

void SwitchButton::setInactiveColor(const QColor &color)
{
    Q_D(SwitchButton);
    d->inactiveColor = color;
    d->setupProperties();
}

QColor SwitchButton::inactiveColor() const
{
    Q_D(const SwitchButton);
    return d->inactiveColor;
}

void SwitchButton::setTrackColor(const QColor &color)
{
    Q_D(SwitchButton);
    d->trackColor = color;
    d->setupProperties();
}

QColor SwitchButton::trackColor() const
{
    Q_D(const SwitchButton);
    return d->trackColor;

}

void SwitchButton::setActiveText(const QString &text)
{
    Q_D(SwitchButton);
    d->activeText = text;
    d->setupProperties();
}

QString SwitchButton::activeText() const
{
    Q_D(const SwitchButton);
    return d->activeText;
}

void SwitchButton::setInactiveText(const QString &text)
{
    Q_D(SwitchButton);
    d->inactiveText = text;
    d->setupProperties();
}

QString SwitchButton::inactiveText()
{
    Q_D(const SwitchButton);
    return d->inactiveText;
}

void SwitchButton::setOrientation(Qt::Orientation orientation)
{
    Q_D(SwitchButton);
    if (d->orientation == orientation) {
        return;
    }

    d->orientation = orientation;
    updateGeometry();
}

Qt::Orientation SwitchButton::orientation() const
{
    Q_D(const SwitchButton);
    return d->orientation;
}

QSize SwitchButton::sizeHint() const
{
    Q_D(const SwitchButton);

    return Qt::Horizontal == d->orientation
            ? QSize(64, 48)
            : QSize(48, 64);
}

void SwitchButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
}
