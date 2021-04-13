#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include "ui/tabs/maintabwidget.h"
#include "ui/trees/channeltreewidget.h"
#include "ui/controller/maintabcontroller.h"

class SettingData;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    enum class StackPage{
        EmptyPage = 0,
        TabWidgetPage
    };

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

signals:

public slots:
    void onImportFinish(const QMultiMap<QString, SettingData*>& settingMap);


private slots:
    void on_actionImport_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;

    SaveController* m_saveController;
    MainTabController* m_mainTabController;
};

#endif // MAINWINDOW_H
