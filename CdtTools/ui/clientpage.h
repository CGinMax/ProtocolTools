#ifndef CLIENTPAGE_H
#define CLIENTPAGE_H

#include <QWidget>

class ClientPage : public QWidget
{
    Q_OBJECT
public:
    explicit ClientPage(QWidget *parent = nullptr);
    ~ClientPage();

    void start();
signals:

public slots:
};
#endif // CLIENTPAGE_H
