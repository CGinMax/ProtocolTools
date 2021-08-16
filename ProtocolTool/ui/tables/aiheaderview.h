#ifndef AIHEADERVIEW_H
#define AIHEADERVIEW_H

#include <QHeaderView>
#include <QScopedPointer>
#include <QCheckBox>

class AiHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    explicit AiHeaderView(Qt::Orientation orientation, QWidget *parent = nullptr);
    ~AiHeaderView() override = default;
protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override;

signals:
    void notifyIsRandom(bool checked);
public slots:

private:
    QScopedPointer<QCheckBox> m_chbRandom;
};

#endif // AIHEADERVIEW_H
