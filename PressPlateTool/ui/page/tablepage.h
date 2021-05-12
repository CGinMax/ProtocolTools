#ifndef TABLEPAGE_H
#define TABLEPAGE_H

#include <QWidget>
#include "../tables/ybtableview.h"

#include "../../protocol/ybprotocolchannel.h"
namespace Ui {
class TablePage;
}

class TablePage : public QWidget
{
    Q_OBJECT

public:
    explicit TablePage(QWidget *parent = nullptr);
    ~TablePage() override;

    void setProtocol(YBProtocolChannel* protocol);
private:
    Ui::TablePage *ui;

    YBTableView* m_table;
    YBProtocolChannel* m_protocol;
};

#endif // TABLEPAGE_H
