#ifndef LISTHEADER_H
#define LISTHEADER_H

#include <QWidget>
namespace Ui {
class ListHeader;
}

class ListHeader : public QWidget
{
    Q_OBJECT
public:
    explicit ListHeader(QWidget *parent = nullptr);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &backgroundColor);

signals:

public slots:

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::ListHeader* ui;
    QColor m_backgroundColor;
};

#endif // LISTHEADER_H
