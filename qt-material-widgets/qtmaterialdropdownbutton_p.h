#ifndef QTMATERIALDROPDOWNBUTTON_P_H
#define QTMATERIALDROPDOWNBUTTON_P_H

#include "qtmaterialraisedbutton_p.h"

class QWidget;
class QFrame;
class QVBoxLayout;
class QtMaterialDropDownButton;
class QtMaterialDropDownButtonPrivate : public QtMaterialRaisedButtonPrivate
{
    Q_DISABLE_COPY(QtMaterialDropDownButtonPrivate)
    Q_DECLARE_PUBLIC(QtMaterialDropDownButton)
public:
    QtMaterialDropDownButtonPrivate(QtMaterialDropDownButton *q);
    ~QtMaterialDropDownButtonPrivate();

    void init();

    QFrame *frame;
    QWidget *listview;

    QVBoxLayout *viewLayout;

};

#endif // QTMATERIALDROPDOWNBUTTON_P_H
