#include "cdtsettingdlg.h"
#include "ui_cdtsettingdlg.h"
#include "../common/util.h"

CDTSettingDlg::CDTSettingDlg(const QSharedPointer<PtCfg> &ptcfg, QWidget *parent)
    : QDialog (parent)
    , m_ptCfg(ptcfg)
    , ui(new Ui::CDTSettingDlg)
{
    ui->setupUi(this);
    initWidgetData(*ptcfg.data());
}

CDTSettingDlg::~CDTSettingDlg()
{
    delete ui;
}

void CDTSettingDlg::initWidgetData(const PtCfg &setting)
{
    ui->cbbProtocol->setCurrentIndex(int(setting.m_protocol));
    ui->edControlType->setText(Util::num2Hex(setting.m_controlType));
    ui->edYxType->setText(Util::num2Hex(setting.m_yxFrameType));
    ui->edYxFuncode->setText(Util::num2Hex(setting.m_yxFuncode));
    ui->edYxNum->setText(Util::num2Hex(setting.m_yxNum));
    ui->edYxStartIo->setText(Util::num2Hex(setting.m_yxStartIo));

    ui->edYcType->setText(Util::num2Hex(setting.m_ycFrameType));
    ui->edYcFuncode->setText(Util::num2Hex(setting.m_ycFuncode));
    ui->edYcNum->setText(Util::num2Hex(setting.m_ycNum));
    ui->edYcStartIo->setText(Util::num2Hex(setting.m_ycStartIo));

    ui->edVYxType->setText(Util::num2Hex(setting.m_vyxFrameType));
    ui->edVYxFuncode->setText(Util::num2Hex(setting.m_vyxFuncode));
    ui->edVYxNum->setText(Util::num2Hex(setting.m_vyxNum));
    ui->edVYxStartIo->setText(Util::num2Hex(setting.m_vyxStartIo));

    ui->edYkReqType->setText(Util::num2Hex(setting.m_ykReqType));
    ui->edYkAckType->setText(Util::num2Hex(setting.m_ykAckType));
    ui->edYkReqCode->setText(Util::num2Hex(setting.m_ykReqCode));
    ui->edYkAckCode->setText(Util::num2Hex(setting.m_ykAckCode));
    ui->edYkExeCode->setText(Util::num2Hex(setting.m_ykExeCode));
    ui->edYkClose->setText(Util::num2Hex(setting.m_ykClose));
    ui->edYkOpen->setText(Util::num2Hex(setting.m_ykOpen));
    ui->edYkLock->setText(Util::num2Hex(setting.m_ykLock));
    ui->edYkUnlock->setText(Util::num2Hex(setting.m_ykUnlock));

    ui->edYxTime->setValue(setting.m_yxTime);
    ui->edYcTime->setValue(setting.m_ycTime);
    ui->edVYxTime->setValue(setting.m_vyxTime);
}


void CDTSettingDlg::on_btnReset_clicked()
{
    initWidgetData(PtCfg());
}

void CDTSettingDlg::on_btnOk_clicked()
{
    m_ptCfg->m_protocol = eProtocol(ui->cbbProtocol->currentIndex());
    m_ptCfg->m_yxFrameType  = Util::hexString2Num(ui->edYxType->text());
    m_ptCfg->m_yxFuncode    = Util::hexString2Num(ui->edYxFuncode->text());
    m_ptCfg->m_yxNum        = Util::hexString2Num(ui->edYxNum->text());
    m_ptCfg->m_yxStartIo    = Util::hexString2Num(ui->edYxStartIo->text());

    m_ptCfg->m_ycFrameType  = Util::hexString2Num(ui->edYcType->text());
    m_ptCfg->m_ycFuncode    = Util::hexString2Num(ui->edYcFuncode->text());
    m_ptCfg->m_ycNum        = Util::hexString2Num(ui->edYcNum->text());
    m_ptCfg->m_ycStartIo    = Util::hexString2Num(ui->edYcStartIo->text());

    m_ptCfg->m_vyxFrameType = Util::hexString2Num(ui->edVYxType->text());
    m_ptCfg->m_vyxFuncode   = Util::hexString2Num(ui->edVYxFuncode->text());
    m_ptCfg->m_vyxNum       = Util::hexString2Num(ui->edVYxNum->text());
    m_ptCfg->m_vyxStartIo   = Util::hexString2Num(ui->edVYxStartIo->text());

    m_ptCfg->m_ykReqType    = Util::hexString2Num(ui->edYkReqType->text());
    m_ptCfg->m_ykAckType    = Util::hexString2Num(ui->edYkAckType->text());
    m_ptCfg->m_ykReqCode    = Util::hexString2Num(ui->edYkReqCode->text());
    m_ptCfg->m_ykAckCode    = Util::hexString2Num(ui->edYkAckCode->text());
    m_ptCfg->m_ykExeCode    = Util::hexString2Num(ui->edYkExeCode->text());
    m_ptCfg->m_ykOpen       = Util::hexString2Num(ui->edYkOpen->text());
    m_ptCfg->m_ykClose      = Util::hexString2Num(ui->edYkClose->text());
    m_ptCfg->m_ykLock       = Util::hexString2Num(ui->edYkLock->text());
    m_ptCfg->m_ykUnlock     = Util::hexString2Num(ui->edYkUnlock->text());

    m_ptCfg->m_yxTime       = ui->edYxTime->value();
    m_ptCfg->m_ycTime       = ui->edYcTime->value();
    m_ptCfg->m_vyxTime      = ui->edVYxTime->value();

    m_ptCfg->clearPoints();

    m_ptCfg->m_globalDiList = new QList<DiData*>;
    for (int i = 0; i < m_ptCfg->m_yxNum; i++) {
        m_ptCfg->m_globalDiList->append(new DiData(m_ptCfg->m_yxStartIo + i, QString("Pt%1").arg(m_ptCfg->m_yxStartIo + i), false));
    }

    m_ptCfg->m_globalAiList = new QList<AiData*>;
    for (int i = 0; i < m_ptCfg->m_ycNum; i++) {
        m_ptCfg->m_globalAiList->append(new AiData(m_ptCfg->m_ycStartIo + i, QString("Pt%1").arg(m_ptCfg->m_ycStartIo + i), 0));
    }
    m_ptCfg->initMap();
    accept();
}

void CDTSettingDlg::on_btnCancel_clicked()
{
    reject();
}

