#include "flatbutton.h"
#include "flatbutton_p.h"


Ui::FlatButtonPrivate::FlatButtonPrivate(Ui::FlatButton* q)
    : RaiseButtonPrivate(q)
{}

Ui::FlatButtonPrivate::~FlatButtonPrivate()
{}

void Ui::FlatButtonPrivate::init()
{
    m_shadowEffect->setEnabled(false);
    m_backgroundColor = QColor(Qt::transparent);
}

Ui::FlatButton::FlatButton(const QString &text, QWidget *parent)
    : RaiseButton(*new FlatButtonPrivate(this), text, parent)
{
    d_func()->init();
}

Ui::FlatButton::~FlatButton()
{

}
