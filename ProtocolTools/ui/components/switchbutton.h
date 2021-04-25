#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QAbstractButton>
#include <QScopedPointer>

class SwitchButtonPrivate;

class SwitchButton : public QAbstractButton
{
    Q_OBJECT

    Q_PROPERTY(QColor disabledColor WRITE setDisabledColor READ disabledColor)
    Q_PROPERTY(QColor activeColor WRITE setActiveColor READ activeColor)
    Q_PROPERTY(QColor inactiveColor WRITE setInactiveColor READ inactiveColor)
    Q_PROPERTY(QColor trackColor WRITE setTrackColor READ trackColor)
    Q_PROPERTY(QString activeText WRITE setActiveText READ activeText)
    Q_PROPERTY(QString inactiveText WRITE setInactiveText READ inactiveText)
public:
    explicit SwitchButton(QWidget *parent = nullptr);
    ~SwitchButton() override;

    void setDisabledColor(const QColor &color);
    QColor disabledColor() const;

    void setActiveColor(const QColor &color);
    QColor activeColor() const;

    void setInactiveColor(const QColor &color);
    QColor inactiveColor() const;

    void setTrackColor(const QColor &color);
    QColor trackColor() const;

    void setActiveText(const QString& text);
    QString activeText() const;

    void setInactiveText(const QString& text);
    QString inactiveText();

    void setOrientation(Qt::Orientation orientation);
    Qt::Orientation orientation() const;

    QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
signals:

public slots:

private:
    Q_DECLARE_PRIVATE(SwitchButton)
    QScopedPointer<SwitchButtonPrivate> d_ptr;
};

#endif // SWITCHBUTTON_H
