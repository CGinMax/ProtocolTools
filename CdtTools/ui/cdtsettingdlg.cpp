#include "cdtsettingdlg.h"
#include "ui_cdtsettingdlg.h"
#include "../common/util.h"

QVector<PtCfg*> CDTSettingDlg::s_defaultCfgs;

CDTSettingDlg::CDTSettingDlg(const QSharedPointer<PtCfg> &ptcfg, QWidget *parent)
    : QDialog (parent)
    , m_ptCfg(ptcfg)
    , ui(new Ui::CDTSettingDlg)
{
    ui->setupUi(this);
    initDefaultCfgs();
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
    ui->edYxNum->setText(QString::number(setting.m_yxNum));
    ui->edYxStartIo->setText(QString::number(setting.m_yxStartIo));

    ui->edYcType->setText(Util::num2Hex(setting.m_ycFrameType));
    ui->edYcFuncode->setText(Util::num2Hex(setting.m_ycFuncode));
    ui->edYcNum->setText(QString::number(setting.m_ycNum));
    ui->edYcStartIo->setText(QString::number(setting.m_ycStartIo));
    ui->cbRandom->setChecked(setting.m_isRandom);

    ui->edVYxType->setText(Util::num2Hex(setting.m_vyxFrameType));
    ui->edVYxFuncode->setText(Util::num2Hex(setting.m_vyxFuncode));
    ui->edVYxNum->setText(QString::number(setting.m_vyxNum));
    ui->edVYxStartIo->setText(QString::number(setting.m_vyxStartIo));

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

void CDTSettingDlg::initDefaultCfgs()
{
    if (!CDTSettingDlg::s_defaultCfgs.isEmpty()) {
        return;
    }
    CDTSettingDlg::s_defaultCfgs.resize(4);

    auto standard = new PtCfg;
    auto interace = new PtCfg;
    interace->m_protocol = eProtocol::CDTGcInterace;
    interace->m_ycFrameType = 0x64;
    interace->m_ykReqType = 0xA8;
    interace->m_ykAckType = 0xA8;
    interace->m_ykReqCode = 0xE0;
    interace->m_ykAckCode = 0xE1;
    interace->m_ykExeCode = 0xE2;

    auto ut = new PtCfg;
    ut->m_protocol = eProtocol::CDTUt;
    ut->m_vyxFrameType = 0xA8;
    ut->m_ykReqType = 0x57;
    ut->m_ykAckType = 0xD9;
    ut->m_ykReqCode = 0xE9;
    ut->m_ykAckCode = 0xEA;
    ut->m_ykExeCode = 0;
    auto nr = new PtCfg;
    nr->m_protocol = eProtocol::CDTNr;
    nr->m_ykReqType = 0xB9;
    nr->m_ykAckType = 0xB9;
    nr->m_ykReqCode = 0x00;
    nr->m_ykAckCode = 0x00;
    nr->m_ykExeCode = 0x00;
    CDTSettingDlg::s_defaultCfgs[0] = standard;
    CDTSettingDlg::s_defaultCfgs[1] = interace;
    CDTSettingDlg::s_defaultCfgs[2] = ut;
    CDTSettingDlg::s_defaultCfgs[3] = nr;
}


void CDTSettingDlg::on_btnReset_clicked()
{
    initWidgetData(*CDTSettingDlg::s_defaultCfgs[ui->cbbProtocol->currentIndex()]);
}

void CDTSettingDlg::on_btnOk_clicked()
{
    m_ptCfg->m_protocol = eProtocol(ui->cbbProtocol->currentIndex());
    m_ptCfg->m_yxFrameType  = Util::hexString2Num(ui->edYxType->text());
    m_ptCfg->m_yxFuncode    = Util::hexString2Num(ui->edYxFuncode->text());
    m_ptCfg->m_yxNum        = ui->edYxNum->text().toInt();
    m_ptCfg->m_yxStartIo    = ui->edYxStartIo->text().toInt();

    m_ptCfg->m_ycFrameType  = Util::hexString2Num(ui->edYcType->text());
    m_ptCfg->m_ycFuncode    = Util::hexString2Num(ui->edYcFuncode->text());
    m_ptCfg->m_ycNum        = ui->edYcNum->text().toInt();
    m_ptCfg->m_ycStartIo    = ui->edYcStartIo->text().toInt();
    m_ptCfg->m_isRandom     = ui->cbRandom->isChecked();

    m_ptCfg->m_vyxFrameType = Util::hexString2Num(ui->edVYxType->text());
    m_ptCfg->m_vyxFuncode   = Util::hexString2Num(ui->edVYxFuncode->text());
    m_ptCfg->m_vyxNum       = ui->edVYxNum->text().toInt();
    m_ptCfg->m_vyxStartIo   = ui->edVYxStartIo->text().toInt();

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

    m_ptCfg->m_globalVDiList = new QList<DiData*>;
    for (int i = 0; i < m_ptCfg->m_vyxNum; i++) {
        m_ptCfg->m_globalVDiList->append(new DiData(m_ptCfg->m_vyxStartIo + i, QString("Pt%1").arg(m_ptCfg->m_vyxStartIo + i), 0));
    }
    m_ptCfg->initMap();
    accept();
}

void CDTSettingDlg::on_btnCancel_clicked()
{
    reject();
}


void CDTSettingDlg::on_cbbProtocol_currentIndexChanged(int index)
{
    initWidgetData(*CDTSettingDlg::s_defaultCfgs[index]);
}
