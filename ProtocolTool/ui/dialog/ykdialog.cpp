#include "ykdialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

YKDialog::YKDialog(const QString &text, QWidget *parent)
    : QDialog(parent)
{
    auto infoLabel = new QLabel(text, this);
    auto btnYes = new QPushButton(tr("Yes"), this);
    auto btnNo = new QPushButton(tr("No"), this);

    auto mainLayout = new QVBoxLayout();
    mainLayout->addWidget(infoLabel);
    auto btnLayout = new QHBoxLayout();
    btnLayout->addSpacing(20);
    btnLayout->addWidget(btnYes);
    btnLayout->addWidget(btnNo);
    btnLayout->addSpacing(20);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(btnLayout);

    setLayout(mainLayout);
    connect(btnYes, &QPushButton::clicked, this, &YKDialog::onBtnYesClicked);
    connect(btnNo, &QPushButton::clicked, this, &YKDialog::onBtnNoClicked);

}

void YKDialog::onBtnYesClicked()
{
    accept();
}

void YKDialog::onBtnNoClicked()
{
    reject();
}


