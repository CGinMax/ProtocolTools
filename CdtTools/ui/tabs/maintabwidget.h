#ifndef MAINTABWIDGET_H
#define MAINTABWIDGET_H

#include <QTabWidget>

class MainTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit MainTabWidget(QWidget *parent = nullptr);

    int addTab(QWidget* widget, const QString& label);
    int addTab(QWidget* widget, const QIcon& icon, const QString& label);

protected:
    void mousePressEvent(QMouseEvent *event) override;
signals:
    void addNewPage();

public slots:
    void onTabCloseRequested(int index);
    void onTabBarClicked(int index);

    void onDivideTab();

private:
    void showContextMenu(int tabIndex);

private:
    int m_lastTabIndex;
    int m_contenxtIndex;
};

#endif // MAINTABWIDGET_H
