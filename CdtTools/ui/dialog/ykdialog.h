#ifndef YKDIALOG_H
#define YKDIALOG_H

#include <QDialog>
#include "../../../qt-material-widgets/qtmaterialdialog.h"


class YKDialog : public QDialog
{
    Q_OBJECT
public:
    explicit YKDialog(const QString& text, QWidget* parent = nullptr);
    ~YKDialog() override = default;

signals:
    void close(int ret);
public slots:
    void onBtnYesClicked();
    void onBtnNoClicked();
    int exec() override;
private:
    QtMaterialDialog* m_dialog;
};

#endif // YKDIALOG_H
