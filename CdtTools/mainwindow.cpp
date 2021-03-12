#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>

#include <QDebug>
#include "ui/tabpage.h"
#include "ui/dialog/nameddialog.h"
#include "common/saveconfig.h"
#include "common/threadpool.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    qRegisterMetaType<QMultiMap<QString, SettingData*>>("QMultiMap<QString, SettingData*>&");
    ui->setupUi(this);
    ui->mainToolBar->hide();

    m_mainTabs = new MainTabWidget(this);
    m_mainTabs->addTab(new TabPage(), tr("Default Page"));
    centralWidget()->layout()->addWidget(m_mainTabs);
    connect(m_mainTabs, &MainTabWidget::addNewPage, this, &MainWindow::onAddNewPage);

    connect(this, &MainWindow::saveFinish, this, &MainWindow::onSaveFinish, Qt::QueuedConnection);
    connect(this, &MainWindow::importFinish, this, &MainWindow::onImportFinish, Qt::QueuedConnection);

    auto screenSize = qApp->primaryScreen()->availableSize();
    setGeometry((screenSize.width() - width()) / 2, (screenSize.height() - height()) / 2, width(), height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddNewPage()
{
    static int pageNum = 1;
    auto defaultName = QString("Page%1").arg(pageNum);
    NamedDialog dlg(defaultName);
    auto ret = dlg.exec();
    if (ret == QDialog::Accepted) {
        auto tabPage = new TabPage(dlg.getNameString(), m_mainTabs);
        m_mainTabs->addTab(tabPage, dlg.getNameString());
        if (!defaultName.compare(dlg.getNameString())) {
            pageNum++;
        }
    }

    m_mainTabs->backToBeforeIndex(ret == QDialog::Rejected);
}

void MainWindow::onSaveFinish(bool success, const QString &msg)
{
    if (success) {
        QMessageBox::information(this, tr("Information"), msg, QMessageBox::Ok);
    }
}

void MainWindow::onImportFinish(QMultiMap<QString, SettingData *> &settingMap)
{
    for (auto iter = settingMap.begin(); iter != settingMap.end(); iter++) {
        m_mainTabs->addTab(new TabPage(QSharedPointer<SettingData>(iter.value()), iter.key()), iter.key());
    }
}


void MainWindow::on_actionImport_triggered()
{
    auto openFileName = QFileDialog::getOpenFileName(this, tr("Open"), QStandardPaths::displayName(QStandardPaths::ApplicationsLocation));
    if (openFileName.isNull()){
        return ;
    }
    ThreadPool::instance()->run([=]{
        try {
            auto tabList = SaveConfig::import(openFileName);
            emit this->importFinish(tabList);

        } catch(std::exception& e) {
            qDebug(e.what());
        }
    });
}

void MainWindow::on_actionSave_triggered()
{
    auto saveFileName = QFileDialog::getSaveFileName(this, tr("Save"), QStandardPaths::displayName(QStandardPaths::DocumentsLocation));
    if (saveFileName.isNull()) {
        return ;
    }
    ThreadPool::instance()->run([=]{
        int tabCount = m_mainTabs->count();
        bool success = false;
        for (int i = 0; i < tabCount - 1; i++) {
            auto tab = qobject_cast<TabPage*>(m_mainTabs->widget(i));
            tab->resetSettingData();
            try {
                success = SaveConfig::saveTabConfig(tab->getSettingData(), tab->getPageName(), saveFileName);
//                QMessageBox::information(this, tr("Information"), tr("Save %1 Success!").arg(saveFileName), QMessageBox::Ok);
            } catch (std::exception& e) {
                qDebug(e.what());
//                QMessageBox::information(this, tr("Information"), tr("Save %1 Failed!").arg(saveFileName), QMessageBox::Ok);
            }
        }
        emit this->saveFinish(success, success ? tr("Save %1 Success!").arg(saveFileName) : tr("Save %1 Failed!").arg(saveFileName));
    });
}
