#ifndef FAKECLOSEBUTTON_H
#define FAKECLOSEBUTTON_H

#include <QAbstractButton>

class FakeCloseButton : public QAbstractButton
{
    Q_OBJECT
public:
    explicit FakeCloseButton(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // FAKECLOSEBUTTON_H
