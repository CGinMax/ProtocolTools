#include "ykdialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

YKDialog::YKDialog(const QString &text, const QString &title, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(title);
    m_infoText.setText(text);
    m_btnYes.setText(QStringLiteral("是"));
    m_btnNo.setText(QStringLiteral("否"));

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(&m_infoText);
    auto btnLayout = new QHBoxLayout(this);
    btnLayout->addSpacing(20);
    btnLayout->addWidget(&m_btnYes);
    btnLayout->addWidget(&m_btnNo);
    btnLayout->addSpacing(20);
    mainLayout->addLayout(btnLayout);

    setLayout(mainLayout);
    connect(&m_btnYes, &QPushButton::clicked, this, &QDialog::accept);
    connect(&m_btnNo, &QPushButton::clicked, this, &QDialog::reject);
}

YKDialog::~YKDialog()
{

}
