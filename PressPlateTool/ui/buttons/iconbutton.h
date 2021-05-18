#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include "raisebutton.h"

namespace Ui {

class RippleEffect;
class IconButtonPrivate;

class IconButton : public RaiseButton
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(IconButton)
    Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)
public:
    explicit IconButton(const QIcon& icon, QWidget *parent = nullptr);
    ~IconButton() override;

    QSize sizeHint() const override;

    IconButton* setOpacity(qreal opacity);
    qreal opacity() const;

    IconButton* setEnabledHover(bool enabled);
    bool enabledHover() const;

    IconButton* setBackgroundEnabled(bool enabled);
    bool backgroundEnabled() const;

protected:
    IconButton(IconButtonPrivate& d, const QIcon& icon, QWidget* parent = nullptr);
    bool event(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

signals:

public slots:

};
}


#endif // ICONBUTTON_H
