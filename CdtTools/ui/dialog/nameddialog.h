#ifndef NAMEDDIALOG_H
#define NAMEDDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
class NamedDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NamedDialog(const QString& defaultName = QString(), QWidget *parent = nullptr);
    ~NamedDialog() = default;

    void setNameString(const QString& name);
    QString getNameString() const;
signals:

public slots:

private slots:
    void onBtnOkClicked();
    void onBtnCancelClicked();

private:
    QLabel m_label;
    QLineEdit m_editName;
    QPushButton m_btnOk;
    QPushButton m_btnCancel;
};

#endif // NAMEDDIALOG_H
