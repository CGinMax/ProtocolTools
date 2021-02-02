#include "ykdialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "../../../qt-material-widgets/qtmaterialflatbutton.h"

YKDialog::YKDialog(const QString &text, QWidget *parent)
    : QDialog(parent)
    , m_dialog(new QtMaterialDialog)
{
    setModal(false);
    setWindowFlag(Qt::FramelessWindowHint);
    resize(parent->width(), parent->height());
    m_dialog->setParent(this);
    auto infoLabel = new QLabel(text, this);
    auto btnYes = new QtMaterialFlatButton(tr("Yes"), Material::Primary, this);
    auto btnNo = new QtMaterialFlatButton(tr("No"), Material::Primary, this);
    btnYes->setHaloVisible(false);
    btnYes->setBackgroundMode(Qt::OpaqueMode);
    btnYes->setOverlayStyle(Material::TintedOverlay);
    btnNo->setHaloVisible(false);
    btnNo->setBackgroundMode(Qt::OpaqueMode);
    btnNo->setOverlayStyle(Material::TintedOverlay);

    auto mainLayout = new QVBoxLayout();
    mainLayout->addWidget(infoLabel);

    auto btnLayout = new QHBoxLayout();
    btnLayout->addSpacing(20);
    btnLayout->addWidget(btnYes);
    btnLayout->addWidget(btnNo);
    btnLayout->addSpacing(20);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(btnLayout);


    m_dialog->setWindowLayout(mainLayout);
    connect(btnYes, &QtMaterialFlatButton::clicked, this, &YKDialog::onBtnYesClicked);
    connect(btnNo, &QtMaterialFlatButton::clicked, this, &YKDialog::onBtnNoClicked);

}

void YKDialog::onBtnYesClicked()
{

    accept();
}

void YKDialog::onBtnNoClicked()
{
    reject();
}

int YKDialog::exec()
{
    m_dialog->showDialog();
    return QDialog::exec();
}


