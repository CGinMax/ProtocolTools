#ifndef FABBUTTON_H
#define FABBUTTON_H

#include "iconbutton.h"

class FabButton : public IconButton
{
    Q_OBJECT
public:
    explicit FabButton(QWidget *parent = nullptr);


    Qt::Corner corner() const;
    void setCorner(Qt::Corner corner);
    int offsetX() const;
    void setOffsetX(int x);

    int offsetY() const;
    void setOffsetY(int y);

    void setOffset(int x, int y);
    void setOffset(const QSize& size);
    QSize offset() const;
protected:
    bool event(QEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    QRect fabGeometry() const;
signals:

public slots:

protected:
    Qt::Corner m_corner;
    int m_offsetX;
    int m_offsetY;
};

#endif // FABBUTTON_H
