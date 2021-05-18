#ifndef FABBUTTON_H
#define FABBUTTON_H

#include "iconbutton.h"

namespace Ui {

class FabButtonPrivate;
class FabButton : public IconButton
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(FabButton)
public:
    explicit FabButton(const QIcon& icon, QWidget *parent = nullptr);
    ~FabButton() override;

    FabButton* setDiameter(int diameter);
    int diameter() const;

    Qt::Corner corner() const;
    FabButton* setCorner(Qt::Corner corner);
    int offsetX() const;
    FabButton* setOffsetX(int x);

    int offsetY() const;
    FabButton* setOffsetY(int y);

    FabButton* setOffset(int x, int y);
    FabButton* setOffset(const QSize& size);
    QSize offset() const;
protected:
    bool event(QEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    QRect fabGeometry() const;
    void updateRippleClipPath() override;
signals:

public slots:

};
}  // namespace Ui


#endif // FABBUTTON_H
