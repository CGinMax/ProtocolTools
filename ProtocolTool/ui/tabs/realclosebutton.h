#ifndef REALCLOSEBUTTON_H
#define REALCLOSEBUTTON_H

#include <QAbstractButton>

class RealCloseButton : public QAbstractButton
{
    Q_OBJECT
public:
    explicit RealCloseButton(QWidget *parent = nullptr);

signals:

public slots:

    // QWidget interface
public:
    QSize sizeHint() const override;

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};

#endif // REALCLOSEBUTTON_H
