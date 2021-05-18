#ifndef RAISEBUTTON_P_H
#define RAISEBUTTON_P_H

#include "abstractbutton_p.h"
#include "../effect/shadoweffect.h"

namespace Ui {

class ShadowEffect;
class RaiseButton;
class RaiseButtonPrivate : public AbstractButtonPrivate
{
    Q_DISABLE_COPY(RaiseButtonPrivate)
    Q_DECLARE_PUBLIC(RaiseButton)
public:
    explicit RaiseButtonPrivate(RaiseButton* q);
    ~RaiseButtonPrivate() override;

    void init();

    ShadowEffect* m_shadowEffect;
    IconAlign m_iconAlign;
};
}  // namespace Ui


#endif // RAISEBUTTON_P_H
