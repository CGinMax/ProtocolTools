#ifndef ICONBUTTON_P_H
#define ICONBUTTON_P_H

#include "raisebutton_p.h"
namespace Ui {

class IconButton;

class IconButtonPrivate : public RaiseButtonPrivate
{
    Q_DISABLE_COPY(IconButtonPrivate)
    Q_DECLARE_PUBLIC(IconButton)
public:
    explicit IconButtonPrivate(IconButton* q);
    ~IconButtonPrivate() override;

    void init();

    bool m_enabledBackground;
    qreal m_opacity;
    bool m_enabledHover;
};
}  // namespace Ui

#endif // ICONBUTTON_P_H
