#ifndef FAICON_H
#define FAICON_H

#include <QObject>
#include "QtAwesome.h"
class FAIcon : public QObject
{
    Q_OBJECT
public:
    static FAIcon* instance();

    QtAwesome* awesome();

    ~FAIcon() override;
signals:
protected:
    explicit FAIcon(QObject *parent = nullptr);
public slots:

private:
    QtAwesome* m_awesomeIcon;
};

#endif // FAICON_H
