#ifndef YKDIALOG_H
#define YKDIALOG_H

#include <QDialog>

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
private:
};

#endif // YKDIALOG_H
