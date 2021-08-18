#ifndef DIHEADERVIEW_H
#define DIHEADERVIEW_H

#include <QObject>
#include <QHeaderView>
#include <QScopedPointer>

#include "../components/switchbutton.h"
class SwitchButton;

class DiHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    explicit DiHeaderView(Qt::Orientation orientation, QWidget *parent = nullptr);
    ~DiHeaderView() override = default;

    // QHeaderView interface
protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override;
signals:
    void notifyAllChanged(bool offon);
public slots:

private slots:


private:
    QScopedPointer<SwitchButton> m_swBtn;
};

#endif // DIHEADERVIEW_H
