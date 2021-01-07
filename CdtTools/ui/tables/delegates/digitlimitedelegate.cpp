#include "digitlimitedelegate.h"
#include <QDebug>

DigitLimiteDelegate::DigitLimiteDelegate(QObject *parent)
    :QItemDelegate(parent)
{

}

QWidget* DigitLimiteDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);

    QLineEdit* editor=new QLineEdit(parent);
    QRegExp regExp("[0-9]{0,10}");
    editor->setValidator(new QRegExpValidator(regExp,parent));
    return editor;
}

void DigitLimiteDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString text=index.model()->data(index,Qt::DisplayRole).toString();
    QLineEdit *lineEdit=static_cast<QLineEdit*>(editor);
    lineEdit->setText(text);
}

void DigitLimiteDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit* lineEdit=static_cast<QLineEdit*>(editor);
    QString text=lineEdit->text();
    model->setData(index,text,Qt::EditRole);
}

void DigitLimiteDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
