#ifndef EDITABLEEVENTFILTER_H
#define EDITABLEEVENTFILTER_H

#include <QObject>

class EditableEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit EditableEventFilter(QObject *parent = nullptr);

signals:

public slots:

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // EDITABLEEVENTFILTER_H
