#ifndef CLIENTPAGE_H
#define CLIENTPAGE_H

#include <QWidget>


namespace Ui {
    class CDTWorkWidget;
} // namespace Ui

class ClientPage : public QWidget
{
    Q_OBJECT
public:
    explicit ClientPage(QWidget *parent = nullptr);
    ~ClientPage();

    void start();
signals:

public slots:

private:
    Ui::CDTWorkWidget *ui;
};

#endif // CLIENTPAGE_H
