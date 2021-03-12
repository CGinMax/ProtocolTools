#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui/tabs/maintabwidget.h"
#include <QPushButton>

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
    void saveFinish(bool success, const QString& msg);
    void importFinish(QMultiMap<QString, SettingData*>& settingMap);

public slots:
    void onAddNewPage();
    void onSaveFinish(bool success, const QString& msg);
    void onImportFinish(QMultiMap<QString, SettingData*>& settingMap);

private slots:
    void on_actionImport_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    MainTabWidget* m_mainTabs;
};

#endif // MAINWINDOW_H
