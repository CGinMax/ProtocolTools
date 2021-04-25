#ifndef DIHEADERVIEW_H
#define DIHEADERVIEW_H

#include <QObject>
#include <QHeaderView>
#include <QComboBox>
#include <QScopedPointer>

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
    void onCbbCurrentIndexChanged(int index);


private:
    QScopedPointer<QComboBox> m_cbb;
};

#endif // DIHEADERVIEW_H
