#ifndef CYCLESENDDIALOG_H
#define CYCLESENDDIALOG_H

#include <QDialog>
#include "../../../qt-material-widgets/qtmaterialdialog.h"

class CycleSendDialog : public QtMaterialDialog
{
    Q_OBJECT
public:
    explicit CycleSendDialog(const QString& msg, QWidget *parent = nullptr);
    ~CycleSendDialog();
signals:

public slots:
};

#endif // CYCLESENDDIALOG_H
