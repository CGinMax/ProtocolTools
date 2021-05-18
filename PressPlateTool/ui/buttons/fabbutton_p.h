#ifndef FABBUTTON_P_H
#define FABBUTTON_P_H

#include "iconbutton_p.h"

namespace Ui {
class FabButton;

class FabButtonPrivate : IconButtonPrivate
{
    Q_DISABLE_COPY(FabButtonPrivate)
    Q_DECLARE_PUBLIC(FabButton)
public:
    explicit FabButtonPrivate(FabButton* q);
    ~FabButtonPrivate() override;

    void init();

    int m_diameter;
    Qt::Corner m_corner;
    int m_xoffset;
    int m_yoffset;
};
}  // namespace Ui

#endif // FABBUTTON_P_H
