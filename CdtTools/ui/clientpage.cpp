#include "clientpage.h"
#include "ui_cdtworkwidget.h"

ClientPage::ClientPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CDTWorkWidget())
{
    ui->setupUi(this);

}

ClientPage::~ClientPage()
{
    delete ui;
}

void ClientPage::start()
{

}
