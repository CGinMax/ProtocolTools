#ifndef EXPANDTILE_H
#define EXPANDTILE_H

#include <QWidget>
#include "tileicon.h"
#include "../editableeventfilter.h"

class QLineEdit;
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
    void setHardwareVersion(const QString& ver);
    void setSoftwareVersion(const QString& ver);
    void setProductDescript(const QString& desc);

    void setChecked(bool checked);
    bool checked() const;

    void setEventFilter(QLineEdit* edit);
signals:
    void queryVersion();
    void toggled(bool checked);
    void titleChanged(const QString& name);
    void deleteItem();
public slots:
protected:
    void mousePressEvent(QMouseEvent *event) override;
protected:
    Ui::ExpandTile* ui;
    TileIcon* m_icon;
    bool m_checked;
private slots:

private:
    EditableEventFilter* m_editFilter;
};

#endif // EXPANDTILE_H
