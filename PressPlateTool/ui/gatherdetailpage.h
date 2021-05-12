#ifndef GATHERDETAILPAGE_H
#define GATHERDETAILPAGE_H

#include <QWidget>
#include "tables/ybtableview.h"
#include "page/tablepage.h"
class GatherData;
class GatherController;
class YBProtocolChannel;

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
    void onItemChanged(GatherController* controller);

    void onNameChanged(const QString& name);

    void onAddrChanged(int addr);

private:
    Ui::GatherDetailPage *ui;

    TablePage* m_tablePage;

    QSharedPointer<GatherData> m_gatherData;
};

#endif // GATHERDETAILPAGE_H
