#ifndef RAISEBUTTON_H
#define RAISEBUTTON_H

#include "abstractbutton.h"

namespace Ui {

class RaiseButtonPrivate;

class RaiseButton : public AbstractButton
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(RaiseButton)
public:
    explicit RaiseButton(const QString& text = QString("Button"), QWidget *parent = nullptr);
    explicit RaiseButton(const QIcon &icon, QWidget* parent = nullptr);
    ~RaiseButton() override;

    void setEnabledShadow(bool enabled);
    bool isEnabledShadow() const;


    QSize sizeHint() const override;
protected:
    explicit RaiseButton(RaiseButtonPrivate& d, const QString& text, QWidget* parent = nullptr);
    explicit RaiseButton(RaiseButtonPrivate& d, const QIcon& icon, QWidget* parent = nullptr);
    void paintEvent(QPaintEvent *event) override;

    void drawIcon(QPainter* painter, const QRect& geometry);

signals:

public slots:

protected:


};
}  // namespace Ui


#endif // RAISEBUTTON_H
