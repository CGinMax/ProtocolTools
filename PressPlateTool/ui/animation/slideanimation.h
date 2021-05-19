#ifndef SLIDEANIMATION_H
#define SLIDEANIMATION_H

#include <QWidget>
#include <QPropertyAnimation>
namespace Ui{
class SlideAnimation : public QPropertyAnimation
{
    Q_OBJECT
public:
    explicit SlideAnimation(const QPoint& pos, QObject *parent = nullptr);

    void setSourcePos(const QPoint& pos);
protected:
    QVariant interpolated(const QVariant &from, const QVariant &to, qreal progress) const override;
signals:

public slots:

protected:
    QPoint m_sourcePos;
};
}  // namespace Ui


#endif // SLIDEANIMATION_H
