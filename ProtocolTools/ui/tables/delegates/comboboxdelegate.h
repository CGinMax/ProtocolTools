#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QItemDelegate>
#include <QComboBox>

class  ComboBoxDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    ComboBoxDelegate(QObject* parent=nullptr);

    /**
     * @brief setItems 设置下拉选项
     * @param items 选项列表
     * @return
     */
    void setItems(QStringList items);

    /**
     * @brief createEditor 创建ComboBox
     * @param parent ComboBox父控件
     * @return option ComboBox参数
     * @param index Model序号
     * @return ComboBox
     */
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    /**
     * @brief setEditorData 设置ComboBox显示数据
     * @param editor ComboBox
     * @param index Model序号
     */
    void setEditorData(QWidget* editor,const QModelIndex &index) const override;

    /**
     * @brief setModelData 将ComboBox显示数据写入Model
     * @param editor ComboBox
     * @param model 数据集
     * @param index Model序号
     */
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;


    /**
     * @brief updateEditorGeometry 更新ComboBox的Geometry
     * @param editor ComboBox
     * @param option ComboBox参数
     * @param index Model序号
     */
    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

signals:
    void delegateValueChanged();
public slots:
    void onCurrentTextChange(const QString& s);
private:
    QStringList itemList;//选项列表
};

#endif // COMBOBOXDELEGATE_H
