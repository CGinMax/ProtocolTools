#ifndef OUTLINEBUTTON_P_H
#define OUTLINEBUTTON_P_H

#include "raisebutton_p.h"
namespace Ui {

class OutlineButton;

class OutlineButtonPrivate : public RaiseButtonPrivate
{
    Q_DISABLE_COPY(OutlineButtonPrivate)
    Q_DECLARE_PUBLIC(OutlineButton)
public:
    explicit OutlineButtonPrivate(OutlineButton* q);
    ~OutlineButtonPrivate() override;

    void init();
};
} // namespace Ui

#endif // OUTLINEBUTTON_P_H
