#ifndef EXPANDTILE_H
#define EXPANDTILE_H

#include <QWidget>
#include "tileicon.h"
#include "../editableeventfilter.h"
namespace Ui {
class ExpandTile;
}

class ExpandTile : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool checked WRITE setChecked READ checked NOTIFY toggled)
public:
    explicit ExpandTile(const QString& title = QString(), QWidget *parent = nullptr);
    ~ExpandTile() override;

    void setTitle(const QString& title);

    void setChecked(bool checked);
    bool checked() const;

    void setEventFilter(QWidget* widget);
signals:
    void toggled(bool checked);
public slots:

protected:
    Ui::ExpandTile* ui;
    void mousePressEvent(QMouseEvent *event) override;
    TileIcon* m_icon;
    bool m_checked;
private:
    EditableEventFilter* m_editFilter;
};

#endif // EXPANDTILE_H
