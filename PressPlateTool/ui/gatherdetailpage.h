#ifndef GATHERDETAILPAGE_H
#define GATHERDETAILPAGE_H

#include <QWidget>
#include "tables/ybtableview.h"

namespace Ui {
class GatherDetailPage;
}

class GatherDetailPage : public QWidget
{
    Q_OBJECT

public:
    explicit GatherDetailPage(QWidget *parent = nullptr);
    ~GatherDetailPage() override;

private:
    Ui::GatherDetailPage *ui;

    YBTableView* m_table;
};

#endif // GATHERDETAILPAGE_H
