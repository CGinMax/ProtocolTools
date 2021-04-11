#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include "ui/tabs/maintabwidget.h"
#include "ui/trees/channeltreewidget.h"
#include "ui/controller/stackedcontroller.h"

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
//    void onAddNewPage();
    void onImportFinish(const QMultiMap<QString, SettingData*>& settingMap);

    void onAddNewPage(TabPage* page, eNetworkType type);

    void onRemovePage(TabPage* page, eNetworkType type);

    void onChangePageName(TabPage* page, eNetworkType type);

private slots:
    void on_actionImport_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    ChannelTreeWidget* m_treeWidget;
    QSplitter* m_mainSplitter;
    MainTabWidget* m_tcpClientTabs;
    MainTabWidget* m_tcpServerTabs;
    MainTabWidget* m_udpTabs;
    SaveController* m_saveController;
    StackedController* m_stackedController;
};

#endif // MAINWINDOW_H
