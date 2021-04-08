#include "comboboxdelegate.h"
#include <QMessageBox>

ComboBoxDelegate::ComboBoxDelegate(QObject *parent)
    :QItemDelegate(parent)
{

}

void ComboBoxDelegate::setItems(QStringList items)
{
    itemList = items;
}

QWidget* ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/) const
{
    QComboBox* editor=new QComboBox(parent);
    editor->addItems(itemList);
    editor->installEventFilter(const_cast<ComboBoxDelegate*>(this));
    editor->setCurrentIndex(0);
    connect(editor, &QComboBox::currentTextChanged, this, &ComboBoxDelegate::onCurrentTextChange);
    return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString text=index.model()->data(index,Qt::DisplayRole).toString();
    QComboBox *comboBox=static_cast<QComboBox*>(editor);
    int curIndex=comboBox->findText(text);
    comboBox->setCurrentIndex(curIndex);
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox* comboBox=static_cast<QComboBox*>(editor);
    QString text=comboBox->currentText();
    model->setData(index,text,Qt::EditRole);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(editor);
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}

void ComboBoxDelegate::onCurrentTextChange(const QString &s)
{
    Q_UNUSED(s)
    emit commitData(qobject_cast<QComboBox*>(sender()));
    emit delegateValueChanged();
}
