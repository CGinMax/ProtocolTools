#ifndef FLOATBUTTONGROUP_H
#define FLOATBUTTONGROUP_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

class FloatButtonGroup : public QWidget
{
    Q_OBJECT
public:
    explicit FloatButtonGroup(QWidget *parent = nullptr);
    ~FloatButtonGroup() override;
    void setLayoutSpacing(int spacing);
    void addButton(QAbstractButton* btn);
    void insertButton(int index, QAbstractButton* btn);
protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
signals:

public slots:

private:
    QHBoxLayout* m_layout;

};

#endif // FLOATBUTTONGROUP_H
