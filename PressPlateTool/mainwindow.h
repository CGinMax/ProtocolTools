#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui/buttons/fabcircularmenu.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static int createNo;

public slots:
    void onNotifyAddOne();

    void onNotifyAddMulti();

private:
    Ui::MainWindow *ui;
    FabCircularMenu* m_fabMenu;
};

#endif // MAINWINDOW_H
