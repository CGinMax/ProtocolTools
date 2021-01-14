#ifndef YKDIALOG_H
#define YKDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>

class YKDialog : public QDialog
{
    Q_OBJECT
public:
    explicit YKDialog(const QString& text, const QString& title=QString(), QWidget* parent = nullptr);
    ~YKDialog() override;

private:
    QLabel m_infoText;
    QPushButton m_btnYes;
    QPushButton m_btnNo;
};

#endif // YKDIALOG_H
