#ifndef GATHERPAGE_H
#define GATHERPAGE_H

#include <QWidget>
#include "../expand/gathercontroller.h"
#include "../expand/expandwidgetitem.h"
namespace Ui {
class GatherPage;
}

class GatherPage : public QWidget
{
    Q_OBJECT

public:
    explicit GatherPage(QWidget *parent = nullptr);
    ~GatherPage() override;

    void addExpandItem(ExpandWidgetItem* item);
signals:

    void itemChanged(GatherController* controller);
private:
    Ui::GatherPage *ui;
};

#endif // GATHERPAGE_H
