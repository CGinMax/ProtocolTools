#ifndef SNACKBAR_H
#define SNACKBAR_H

#include <QWidget>
#include <QIcon>
#include <QLabel>
#include "../base/base_type.h"

namespace Ui {
class FlatButton;
class SnackBarPrivate;
class SnackBar : public QWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(SnackBar)
    Q_PROPERTY(QPoint distance WRITE setDistance)
public:
    explicit SnackBar(const QString& text, QWidget *parent = nullptr);
    explicit SnackBar(const QIcon& icon, const QString& text, QWidget* parent = nullptr);
    ~SnackBar() override;

    SnackBar* setText(const QString& text);
    QString text() const;

    SnackBar* setTextFlag(int flag, bool enabled = true);
    int textFlags() const;

    SnackBar* setBackgroundColor(const QColor& color);
    QColor backgroundColor() const;

    SnackBar* setTextColor(const QColor& color);
    QColor textColor() const;

    SnackBar* setIcon(const QIcon& icon);
    QIcon icon() const;

    SnackBar* setIconSize(const QSize& size);
    QSize iconSize() const;

    SnackBar* setRadius(int radius);
    int radius() const;

    SnackBar* setClickToDismiss(bool enabled);
    bool clickToDismiss() const;

    SnackBar* setDistance(const QPoint& pos);

    SnackBar* setAction(const QString& text, Fn<void()>&& callback);

    SnackBar* setEnabledShadow(bool enabled);
    bool isShadowEnabled() const;

    SnackBar* setAnimationDuration(int duration);
    int animationDuration() const;

    SnackBar* setShowDuration(int duration);
    int showDuration() const;

    QSize sizeHint() const override;

    void setEnabledAnimation(bool enabled);

    void showBar(const QPoint& startValue = QPoint(),
                 const QPoint& endValue = QPoint());
    void hideBar();

    bool isFinished();

    void stopWait();

    void setSlidePos(const QPoint& pos);

    static void showSnackBar(QWidget* widget, const QString& text, const QIcon& icon = QIcon(),
                             const QString& actionText = QString(),
                             Fn<void()>&& callback = Fn<void()>());
protected:
    bool event(QEvent *event) override;

    void paintEvent(QPaintEvent *event) override;
    void prepareSlidePos();
    void updateGeometry();
    virtual void updateActionGeometry();
signals:
    void showFinished();

public slots:
    void onActionPressed();

protected slots:
    void onSlideFinished();

protected:
    QScopedPointer<SnackBarPrivate> d_ptr;
};
}  // namespace Ui



#endif // SNACKBAR_H
