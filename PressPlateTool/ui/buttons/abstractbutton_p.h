#ifndef ABSTRACTBUTTON_P_H
#define ABSTRACTBUTTON_P_H

#include <QtGlobal>
#include <QColor>
#include "style.h"

namespace Ui {
class AbstractButton;
class RippleEffect;

class AbstractButtonPrivate
{
    Q_DISABLE_COPY(AbstractButtonPrivate)
    Q_DECLARE_PUBLIC(AbstractButton)
public:
    explicit AbstractButtonPrivate(AbstractButton* q);
    virtual ~AbstractButtonPrivate();

    void init();

    AbstractButton* const q_ptr;
    RippleEffect* m_rippleEffect;
    Ui::RippleStyle m_rippleStyle;

    Qt::BGMode m_bgMode;
    QColor m_backgroundColor;
    QColor m_foregroundColor;
    QColor m_disabledColor;
    QColor m_disabledBackgroundColor;
    QColor m_rippleColor;

    qreal m_opacity;


    int m_xradius;
    int m_yradius;

};
}  // namespace Ui


#endif // ABSTRACTBUTTON_P_H
