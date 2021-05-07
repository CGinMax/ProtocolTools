#ifndef LISTVIEWITEM_H
#define LISTVIEWITEM_H

#include <QWidget>
namespace Ui {
class ListViewItem;
}

class ListViewItem : public QWidget
{
    Q_OBJECT
public:
    explicit ListViewItem(QWidget *parent = nullptr);

    void setId(const QString& id);

    void setVersion(const QString& version);
signals:

public slots:

private:
    Ui::ListViewItem* ui;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // LISTVIEWITEM_H
