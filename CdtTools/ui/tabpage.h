#ifndef TABPAGE_H
#define TABPAGE_H

#include <QWidget>
#include "network/tcpserver.h"
#include "network/tcpclient.h"
namespace Ui {
class TabPage;
}

class TabPage : public QWidget
{
    Q_OBJECT

public:
    explicit TabPage(QWidget *parent = nullptr);
    ~TabPage() override;
    void initWidget();


private slots:
    void on_cbbProtocl_currentIndexChanged(int index);

    void on_btnStart_clicked();

    void on_btnStop_clicked();

private:
    Ui::TabPage *ui;
    QSharedPointer<NetworkBase> m_network;
};

#endif // TABPAGE_H
