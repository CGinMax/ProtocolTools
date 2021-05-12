#ifndef YBTABLEVIEW_H
#define YBTABLEVIEW_H

#include <QListView>
#include "ybtablemodel.h"

class YBTableView : public QListView
{
    Q_OBJECT
public:
    explicit YBTableView(QWidget *parent = nullptr);
    ~YBTableView() override;

    void addYBSensor(int count);

    void clearAllYBSensor();
signals:

public slots:

protected:
    YBTableModel* m_model;
};

#endif // YBTABLEVIEW_H
