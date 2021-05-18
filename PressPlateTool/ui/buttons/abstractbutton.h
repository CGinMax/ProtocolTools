#ifndef ABSTRACTBUTTON_H
#define ABSTRACTBUTTON_H

#include <QScopedPointer>
#include <QAbstractButton>

namespace Ui {
class AbstractButtonPrivate;
enum class RippleStyle;

class AbstractButton : public QAbstractButton
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(AbstractButton)

    Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity NOTIFY opacityChanged)
public:
    explicit AbstractButton(QWidget *parent = nullptr);
    ~AbstractButton() override;

    void setAdaptiveColor(bool enabled);
    bool adaptiveColor() const;

//    void setBgMode()

    AbstractButton* setOpacity(qreal opacity);
    qreal opacity() const;

    AbstractButton* setBackgroundColor(const QColor& color);
    QColor backgroundColor() const;

    AbstractButton* setForegroundColor(const QColor& color);
    QColor foregroundColor() const;

    AbstractButton* setDisabledColor(const QColor& color);
    QColor disabledColor();

    AbstractButton* setDisabledBgColor(const QColor& color);
    QColor diabledBgColor() const;

    AbstractButton* setBorderColor(const QColor& color);
    QColor borderColor() const;

    AbstractButton* setXRadius(int radius);
    int xradius() const;

    AbstractButton* setYRadius(int radius);
    int yradius() const;

    AbstractButton* setEnabledBorder(bool enabled);
    bool borderEnabled() const;

    AbstractButton* setBorderWidth(int width);
    int borderWidth() const;

    AbstractButton* setRippleStyle(RippleStyle style);
    RippleStyle rippleStyle() const;

    AbstractButton* setClipPath(const QPainterPath &path);

protected:
    explicit AbstractButton(AbstractButtonPrivate& d, QWidget* parent = nullptr);

signals:
    void opacityChanged();

public slots:

protected:
    const QScopedPointer<AbstractButtonPrivate> d_ptr;
    bool m_enabledAdaptiveColor;
private:
};

}  // namespace Ui


#endif // ABSTRACTBUTTON_H
