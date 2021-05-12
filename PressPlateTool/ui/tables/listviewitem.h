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

    void setName(const QString& name);
    void setAddress(int addr);
    void setHardwareVersion(const QString& version);
    void setSoftwareVersion(const QString& version);
    void setProductionDescription(const QString& desc);
signals:
    void notifySetAddr(int addr);
    void notifyQueryStatus();
    void notifyQueryVersion();
    void notifyDelete();

public slots:

private:
    Ui::ListViewItem* ui;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
private slots:
    void on_btnSetAddr_clicked();
};

#endif // LISTVIEWITEM_H
