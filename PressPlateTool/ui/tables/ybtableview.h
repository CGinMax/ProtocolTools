#ifndef YBTABLEVIEW_H
#define YBTABLEVIEW_H

#include <QTableView>
#include <QListView>

class YBTableView : public QListView
{
    Q_OBJECT
public:
    explicit YBTableView(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // YBTABLEVIEW_H
