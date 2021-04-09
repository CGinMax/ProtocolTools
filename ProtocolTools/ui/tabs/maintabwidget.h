#ifndef MAINTABWIDGET_H
#define MAINTABWIDGET_H

#include <QTabWidget>
#include "../../common/savecontroller.h"

class MainTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit MainTabWidget(const QSharedPointer<SaveController> saveCtrl, QWidget *parent = nullptr);

    int addTab(QWidget* widget, const QString& label);
    int addTab(QWidget* widget, const QIcon& icon, const QString& label);

    void backToBeforeIndex(bool isBack = false);
signals:
    void addNewPage();

public slots:
    void onTabCloseRequested(int index);
    void onTabBarClicked(int index);
    void onTabAtIndexClicked(int index);
    void onDivideTab();

private:
    void showContextMenu(int tabIndex);

private:
    int m_opendIndex;
    int m_lastTabIndex;
    int m_contenxtIndex;

    QSharedPointer<SaveController> m_saveController;
};

#endif // MAINTABWIDGET_H
