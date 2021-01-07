#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

/********************************************************************************************

   版权所有：珠海华伟电气科技股份有限公司
   版本号　：V1.0
   文件名　ComboBoxDelegate.h
   生成日期：2019-11-28
   作者　　：吴其东
   功能说明：表格视图的显示代理基类，本基类主要用于下拉框选择输入
   注意事项：使用该代理时，需要在table的设置相应列的openPersistentEditor属性

---------------------------------------------------------------------------------------------

   修改记录：
              修改者　　　　*　　　　修改日期　　　　*　　　　修改原因　　　　*　　　　修改内容
   记录1：　　　　　　　　　　*　　　　　　　　　　　　*　　　　　　　　　　　　*

***********************************************************************************************/

#include <QItemDelegate>
#include <QComboBox>

class  ComboBoxDelegate : public QItemDelegate
{
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

private:
    QStringList itemList;//选项列表
};

#endif // COMBOBOXDELEGATE_H
