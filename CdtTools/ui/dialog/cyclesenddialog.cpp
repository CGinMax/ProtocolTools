#include "cyclesenddialog.h"
#include "../../../qt-material-widgets/qtmaterialflatbutton.h"
#include <QVBoxLayout>
#include <QLabel>

CycleSendDialog::CycleSendDialog(const QString &msg, QWidget *parent) : QtMaterialDialog(parent)
{
    auto layout = new QVBoxLayout();
    auto infoLabel = new QLabel(msg, this);
    layout->addWidget(infoLabel);
    auto btnCancle = new QtMaterialFlatButton(tr("取消"), Material::Default, this);
    btnCancle->setOverlayStyle(Material::OverlayStyle::TintedOverlay);
    btnCancle->setBackgroundMode(Qt::OpaqueMode);
    btnCancle->setHaloVisible(false);
    layout->addWidget(btnCancle);
    layout->setAlignment(btnCancle, Qt::AlignBottom | Qt::AlignCenter);
    connect(btnCancle, &QPushButton::clicked, this, &QtMaterialDialog::hideDialog);
    setWindowLayout(layout);
}

CycleSendDialog::~CycleSendDialog()
{

}
