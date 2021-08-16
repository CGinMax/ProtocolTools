#ifndef SWITCHBUTTON_INTERNAL_H
#define SWITCHBUTTON_INTERNAL_H

#include <QWidget>
class SwitchButton;

class SwitchButtonThumb : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal shift WRITE setShift READ shift)
    Q_PROPERTY(qreal thumbWidth WRITE setThumbWidth READ thumbWidth)
    Q_PROPERTY(QColor thumbColor WRITE setThumbColor READ thumbColor)
public:
    explicit SwitchButtonThumb(SwitchButton* parent);
    ~SwitchButtonThumb() override;

    void setShift(qreal shift);
    inline qreal shift() const;

    void setThumbWidth(qreal thumbWidth);
    inline qreal thumbWidth() const;

    inline qreal offset() const;

    inline void setThumbColor(const QColor& color);
    inline QColor thumbColor() const;
protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    void updateOffset();
    Q_DISABLE_COPY(SwitchButtonThumb)

    SwitchButton*     m_switchBtn;
    QColor                  m_thumbColor;
    qreal                   m_shift;
    qreal                   m_thumbWidth;
    qreal                   m_offset;
    int m_leftPadding;

};

inline qreal SwitchButtonThumb::shift() const
{
    return m_shift;
}

inline qreal SwitchButtonThumb::thumbWidth() const
{
    return m_thumbWidth;
}

inline qreal SwitchButtonThumb::offset() const
{
    return m_offset;
}

inline void SwitchButtonThumb::setThumbColor(const QColor &color)
{
    m_thumbColor = color;
    update();
}

inline QColor SwitchButtonThumb::thumbColor() const
{
    return  m_thumbColor;
}

class SwitchButtonTrack : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor trackColor WRITE setTrackColor READ trackColor)
public:
    explicit SwitchButtonTrack(SwitchButton* parent);
    ~SwitchButtonTrack() override;

    void setTrackColor(const QColor& color);
    inline QColor trackColor() const;

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
private:
    Q_DISABLE_COPY(SwitchButtonTrack)

    SwitchButton* m_switchBtn;
    QColor              m_trackColor;
};

QColor SwitchButtonTrack::trackColor() const
{
    return m_trackColor;
}

#endif // SWITCHBUTTON_INTERNAL_H
