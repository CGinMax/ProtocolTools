#ifndef DIGITLIMITEDELEGATE_H
#define DIGITLIMITEDELEGATE_H

/********************************************************************************************

   版权所有：珠海华伟电气科技股份有限公司
   版本号　：V1.0
   文件名　DigitLimiteDelegate.h
   生成日期：2019-11-28
   作者　　：吴其东
   功能说明：表格视图的显示代理基类，本基类主要用于通过正则表达式限制数字输入范围(QLineEdit)
   注意事项：使用该代理时，需要在table的设置相应列的openPersistentEditor属性
---------------------------------------------------------------------------------------------

   修改记录：
              修改者　　　　*　　　　修改日期　　　　*　　　　修改原因　　　　*　　　　修改内容
   记录1：　　　　　　　　　　*　　　　　　　　　　　　*　　　　　　　　　　　　*

***********************************************************************************************/

#include <QItemDelegate>
#include <QLineEdit>
#include <QRegExp>

class  DigitLimiteDelegate : public QItemDelegate
{
public:
    DigitLimiteDelegate(QObject* parent=nullptr);

    /**
     * @brief createEditor 创建LineEdit
     * @param parent LineEdit父控件
     * @return option LineEdit参数
     * @param index Model序号
     * @return LineEdit
     */
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    /**
     * @brief setEditorData 设置LineEdit显示数据
     * @param editor LineEdit
     * @param index Model序号
     */
    void setEditorData(QWidget* editor,const QModelIndex &index) const override;

    /**
     * @brief setModelData 将LineEdit显示数据写入Model
     * @param editor LineEdit
     * @param model 数据集
     * @param index Model序号
     */
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    /**
     * @brief updateEditorGeometry 更新LineEdit的Geometry
     * @param editor Date
     * @param option Date参数
     * @param index Model序号
     */
    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;
};

#endif // DIGITLIMITEDELEGATE_H
