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
    ~MainWindow() override;

    static int createNo;

    static void showSnackBar(const QString& text, const QIcon& icon = QIcon());

public slots:
    void onNotifyAddOne();

    void onNotifyAddMulti();

private slots:

private:
    Ui::MainWindow *ui;
    FabCircularMenu* m_fabMenu;
};

#endif // MAINWINDOW_H
