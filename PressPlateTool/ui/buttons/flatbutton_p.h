#ifndef FLATBUTTON_P_H
#define FLATBUTTON_P_H

#include "raisebutton_p.h"
namespace Ui {

class FlatButton;
class FlatButtonPrivate : public RaiseButtonPrivate
{
    Q_DISABLE_COPY(FlatButtonPrivate)
    Q_DECLARE_PUBLIC(FlatButton)
public:
    explicit FlatButtonPrivate(FlatButton* q);
    ~FlatButtonPrivate() override;

    void init();
};
}  // namespace Ui


#endif // FLATBUTTON_P_H
