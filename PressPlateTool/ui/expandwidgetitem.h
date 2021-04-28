#ifndef EXPANDWIDGETITEM_H
#define EXPANDWIDGETITEM_H

#include <QWidget>
#include <QScopedPointer>
#include <QParallelAnimationGroup>
#include <QScrollArea>

#include "expandtile.h"

class ExpandWidgetItemPrivate;

class ExpandWidgetItem : public QWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(ExpandWidgetItem)
    Q_PROPERTY(bool isExpanded WRITE setExpanded READ expanded NOTIFY expandedChanged)
public:
    explicit ExpandWidgetItem(ExpandTile* tile, QWidget *parent = nullptr);
    ~ExpandWidgetItem() override;

    void setContentWidget(QWidget* widget);

    void updateContentAnimation();


    QColor color() const;
    void setBorderColor(const QColor &color);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor& color);

    int borderRadius() const;
    void setBorderRadius(int radius);

    bool expanded() const;
    void setExpanded(bool expanded);

signals:
    void expandedChanged(bool expanded);
public slots:
    void expand(bool needExpanded);


protected:
    bool event(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    const QScopedPointer<ExpandWidgetItemPrivate> d_ptr;
    ExpandTile* m_tile;
    QWidget* m_contentArea;
    QParallelAnimationGroup* m_transitionAimation;
private:
};

#endif // EXPANDWIDGETITEM_H
