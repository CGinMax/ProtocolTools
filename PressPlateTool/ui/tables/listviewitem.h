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
    explicit ListViewItem(const QString& name = QString("Sensor#"), QWidget *parent = nullptr);
    explicit ListViewItem(int address, QWidget* parent = nullptr);

    void setName(const QString& name);
    void setAddress(int addr);
    int  address() const;
    void setCurrentStatus(int status);
    void setConfigedStatus(int status);
    void setHardwareVersion(const QString& version);
    void setSoftwareVersion(const QString& version);
    void setProductionDescription(const QString& desc);
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    void initWidget();
signals:
    void notifySetAddr(int addr);
    void notifyQueryStatus(int addr);
    void notifyQueryVersion(int addr);
    void notifyDelete();
    void statusChanged(int addr, int status);

public slots:

private slots:
    void on_cbbChangeStatus_currentIndexChanged(int index);

private:
    Ui::ListViewItem* ui;

};

#endif // LISTVIEWITEM_H
