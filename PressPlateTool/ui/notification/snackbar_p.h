#ifndef SNACKBAR_P_H
#define SNACKBAR_P_H

#include <QIcon>
#include <QColor>
#include <QBasicTimer>
#include "../base/base_type.h"

class QLabel;
namespace Ui {
class FlatButton;
class ShadowEffect;
class SlideAnimation;
class SnackBar;

class SnackBarPrivate
{
    Q_DISABLE_COPY(SnackBarPrivate)
    Q_DECLARE_PUBLIC(SnackBar)
public:
    explicit SnackBarPrivate(SnackBar* q);
    virtual ~SnackBarPrivate();

    void init(const QIcon& icon, const QString& text);

    SnackBar* const q_ptr;
    ShadowEffect* m_shadowEffect;
    QColor m_backgroundColor;
    QColor m_textColor;
    QIcon m_icon;
    QSize m_iconSize;
    int m_radius;
    bool m_clickDismiss;

    QString m_text;
    int m_textFlag;
    FlatButton* m_actionBtn;
    Fn<void()> m_actionCallback;

    SlideAnimation* m_slideAnimation;
    int m_animationDuration;

    QBasicTimer m_timer;
    int m_showDuration;
};
}  // namespace Ui

#endif // SNACKBAR_P_H
