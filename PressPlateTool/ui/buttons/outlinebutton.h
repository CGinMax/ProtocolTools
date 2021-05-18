#ifndef OUTLINEBUTTON_H
#define OUTLINEBUTTON_H

#include "raisebutton.h"
namespace Ui {

class OutlineButtonPrivate;
class OutlineButton : public RaiseButton
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(OutlineButton)
public:
    explicit OutlineButton(const QString& text = QString("Button"), QWidget* parent = nullptr);
    ~OutlineButton() override;
};

}  // namespace Ui

#endif // OUTLINEBUTTON_H
