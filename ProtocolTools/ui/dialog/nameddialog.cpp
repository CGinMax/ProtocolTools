#include "nameddialog.h"
#include <QGridLayout>

NamedDialog::NamedDialog(const QString &defaultName, QWidget *parent)
    : QDialog(parent)
{
    connect(&m_editName, &QLineEdit::textChanged, this, [=](const QString& text){
        m_btnOk.setEnabled(!text.isEmpty());
    });

    m_label.setText("Name:");
    m_editName.setText(defaultName);
    m_btnOk.setText(tr("Ok"));
    m_btnCancel.setText(tr("Cancel"));
    auto mainlayout = new QGridLayout(this);
    mainlayout->addWidget(&m_label, 0, 0);
    mainlayout->addWidget(&m_editName, 0, 1);
    mainlayout->addWidget(&m_btnOk, 1, 0);
    mainlayout->addWidget(&m_btnCancel, 1, 1);

    connect(&m_btnOk, &QPushButton::clicked, this, &NamedDialog::onBtnOkClicked);
    connect(&m_btnCancel, &QPushButton::clicked, this, &NamedDialog::onBtnCancelClicked);
}

void NamedDialog::setNameString(const QString &name)
{
    m_editName.setText(name);
}

QString NamedDialog::getNameString() const
{
    return m_editName.text();
}

void NamedDialog::onBtnOkClicked()
{
    accept();
}

void NamedDialog::onBtnCancelClicked()
{
    reject();
}
