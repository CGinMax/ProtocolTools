#ifndef SWITCHBUTTON_P_H
#define SWITCHBUTTON_P_H

#include <Qt>
#include <QColor>
class QStateMachine;
class QState;
class SwitchButton;
class SwitchButtonThumb;
class SwitchButtonTrack;

class SwitchButtonPrivate
{
    Q_DISABLE_COPY(SwitchButtonPrivate)
    Q_DECLARE_PUBLIC(SwitchButton)
public:
    explicit SwitchButtonPrivate(SwitchButton *q);
    ~SwitchButtonPrivate();

    void init();
    void setupProperties();

    SwitchButton              *q_ptr;
    SwitchButtonThumb         *thumb;
    SwitchButtonTrack         *track;
    QStateMachine             *stateMachine;
    QState                    *offState;
    QState                    *onState;
    Qt::Orientation            orientation;
    QColor                     disabledColor;
    QColor                     activeColor;
    QColor                     inactiveColor;
    QColor                     trackColor;
    QString                    activeText;
    QString                    inactiveText;
};

#endif // SWITCHBUTTON_P_H
