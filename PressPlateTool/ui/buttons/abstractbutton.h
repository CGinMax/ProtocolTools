#ifndef ABSTRACTBUTTON_H
#define ABSTRACTBUTTON_H

#include <QScopedPointer>
#include <QAbstractButton>

namespace Ui {
class AbstractButtonPrivate;

class AbstractButton : public QAbstractButton
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AbstractButton)
public:
    explicit AbstractButton(QWidget *parent = nullptr);
    ~AbstractButton() override;
signals:


public slots:

protected:

    const QScopedPointer<AbstractButtonPrivate> d_ptr;
private:

};

}


#endif // ABSTRACTBUTTON_H
