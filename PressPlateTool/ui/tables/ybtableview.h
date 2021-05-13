#ifndef YBTABLEVIEW_H
#define YBTABLEVIEW_H

#include <QListView>
#include "ybtablemodel.h"

class ListViewItem;

class YBTableView : public QListView
{
    Q_OBJECT
public:
    explicit YBTableView(QWidget *parent = nullptr);
    ~YBTableView() override;

    int sensorCount() const;

    void setListItemAddr(int index, int addr);
    int getListItemAddr(int index);

    void setListItemStatus(int index, uint8_t curStatus, uint8_t configedStatus);

    void setListItemVersion(int index, const QString& hardVer, const QString& softVer, const QString& productDesc);

    void setListItemConfigedStatus(int index, uint8_t status);

    void addYBSensor(int count);

    void deleteYBSensor(int first, int last);
    void deleteAllYBSensor();
signals:
    void setSensorAddr(int index, int addr);
    void querySensorStatus(int index, int addr);
    void querySensorVersion(int index, int addr);
    void changeSensorStatus(int index, int addr, int status);

public slots:
    void onNotifyDelete();

protected:
    QList<ListViewItem*> m_itemList;
    YBTableModel* m_model;
};

#endif // YBTABLEVIEW_H
