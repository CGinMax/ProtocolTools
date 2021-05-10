#ifndef GATHERDETAILPAGE_H
#define GATHERDETAILPAGE_H

#include <QWidget>
#include "tables/ybtableview.h"
#include "common/gatherdata.h"

namespace Ui {
class GatherDetailPage;
}

class GatherDetailPage : public QWidget
{
    Q_OBJECT

public:
    explicit GatherDetailPage(QWidget *parent = nullptr);
    ~GatherDetailPage() override;

public slots:
    void onItemChanged(const QSharedPointer<GatherData>& gatherData);

    void onNameChanged(const QString& name);

    void onAddrChanged(int addr);

private:
    Ui::GatherDetailPage *ui;

    YBTableView* m_table;

    QSharedPointer<GatherData> m_gatherData;
};

#endif // GATHERDETAILPAGE_H
