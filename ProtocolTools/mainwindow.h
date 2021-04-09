#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui/tabs/maintabwidget.h"

class SettingData;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

signals:

public slots:
    void onAddNewPage();
    void onImportFinish(const QMultiMap<QString, SettingData*>& settingMap);

private slots:
    void on_actionImport_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    MainTabWidget* m_mainTabs;
    QSharedPointer<SaveController> m_saveController;
};

#endif // MAINWINDOW_H
