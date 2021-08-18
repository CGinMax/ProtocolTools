#include "comboboxdelegate.h"
#include <QMessageBox>
#include "../../components/switchbutton.h"

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
    auto editor = new SwitchButton(parent);
    editor->setTrackMargins(QMargins(15, 5, 15, 5));
//    QComboBox* editor=new QComboBox(parent);
//    editor->addItems(itemList);
    editor->installEventFilter(const_cast<ComboBoxDelegate*>(this));
    connect(editor, &SwitchButton::toggled, this, &ComboBoxDelegate::onToggled);
//    editor->setCurrentIndex(0);
//    connect(editor, &QComboBox::currentTextChanged, this, &ComboBoxDelegate::onCurrentTextChange);
    return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    bool offOn = index.model()->data(index, Qt::DisplayRole).toBool();
    auto btn = static_cast<SwitchButton*>(editor);
    btn->setChecked(offOn);
//    QString text=index.model()->data(index,Qt::DisplayRole).toString();
//    QComboBox *comboBox=static_cast<QComboBox*>(editor);
//    int curIndex=comboBox->findText(text);
//    comboBox->setCurrentIndex(curIndex);
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    auto btn = static_cast<SwitchButton*>(editor);
    bool offOn = btn->isChecked();
    model->setData(index, offOn, Qt::EditRole);
//    QComboBox* comboBox=static_cast<QComboBox*>(editor);
//    QString text=comboBox->currentText();
//    model->setData(index,text,Qt::EditRole);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(editor);
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}

void ComboBoxDelegate::onToggled(bool toggled)
{
    Q_UNUSED(toggled)
    emit commitData(qobject_cast<QWidget*>(sender()));
    emit delegateValueChanged();
}
