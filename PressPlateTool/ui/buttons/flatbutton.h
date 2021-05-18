#ifndef FLATBUTTON_H
#define FLATBUTTON_H

#include "raisebutton.h"

namespace Ui {
class FlatButtonPrivate;

class FlatButton : public RaiseButton
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(FlatButton)
public:
    explicit FlatButton(const QString& text = QString("Button"), QWidget* parent = nullptr);
    ~FlatButton() override;
};

}  // namespace Ui


#endif // FLATBUTTON_H
