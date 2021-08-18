#include "cdtsettingdlg.h"
#include "ui_cdtsettingdlg.h"
#include "../common/util.h"
#include <exception>
#include <QFileDialog>
#include <QStandardPaths>

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
    ui->txtYxSheetInfo->setHidden(true);

    ui->edYcType->setText(Util::num2Hex(setting.m_ycFrameType));
    ui->edYcFuncode->setText(Util::num2Hex(setting.m_ycFuncode));
    ui->edYcNum->setText(QString::number(setting.m_ycNum));
    ui->edYcStartIo->setText(QString::number(setting.m_ycStartIo));
    ui->txtYcSheetInfo->setHidden(true);

    ui->edVYxType->setText(Util::num2Hex(setting.m_vyxFrameType));
    ui->edVYxFuncode->setText(Util::num2Hex(setting.m_vyxFuncode));
    ui->edVYxNum->setText(QString::number(setting.m_vyxNum));
    ui->edVYxStartIo->setText(QString::number(setting.m_vyxStartIo));
    ui->txtVYxSheetInfo->setHidden(true);

    ui->edYkReqType->setText(Util::num2Hex(setting.m_ykReqType));
    ui->edYkAckType->setText(Util::num2Hex(setting.m_ykAckType));
    ui->edYkReqCode->setText(Util::num2Hex(setting.m_ykReqCode));
    ui->edYkAckCode->setText(Util::num2Hex(setting.m_ykAckCode));
    ui->edYkExeCode->setText(Util::num2Hex(setting.m_ykExeCode));
    ui->edYkClose->setText(Util::num2Hex(setting.m_ykClose));
    ui->edYkOpen->setText(Util::num2Hex(setting.m_ykOpen));
    ui->edYkLock->setText(Util::num2Hex(setting.m_ykLock));
    ui->edYkUnlock->setText(Util::num2Hex(setting.m_ykUnlock));

    ui->edYxTime->setValue(static_cast<int>(setting.m_yxTime));
    ui->edYcTime->setValue(static_cast<int>(setting.m_ycTime));
    ui->edVYxTime->setValue(static_cast<int>(setting.m_vyxTime));

}

void CDTSettingDlg::initDefaultCfgs()
{
    if (!CDTSettingDlg::s_defaultCfgs.isEmpty()) {
        return;
    }
    CDTSettingDlg::s_defaultCfgs.resize(5);

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
    auto nrudp = new PtCfg;
    nrudp->m_protocol = eProtocol::NRUdp;

    CDTSettingDlg::s_defaultCfgs[0] = standard;
    CDTSettingDlg::s_defaultCfgs[1] = interace;
    CDTSettingDlg::s_defaultCfgs[2] = ut;
    CDTSettingDlg::s_defaultCfgs[3] = nr;
    CDTSettingDlg::s_defaultCfgs[4] = nrudp;
}


void CDTSettingDlg::on_btnReset_clicked()
{
    initWidgetData(*CDTSettingDlg::s_defaultCfgs[ui->cbbProtocol->currentIndex()]);
}

void CDTSettingDlg::on_btnOk_clicked()
{
    m_ptCfg->m_protocol     = eProtocol(ui->cbbProtocol->currentIndex());
    m_ptCfg->m_yxFrameType  = Util::hexString2Num(ui->edYxType->text());
    m_ptCfg->m_yxFuncode    = Util::hexString2Num(ui->edYxFuncode->text());
    m_ptCfg->m_yxNum        = ui->edYxNum->text().toInt();
    m_ptCfg->m_yxStartIo    = ui->edYxStartIo->text().toInt();
    if (ui->edYxNum->isEnabled()) {
        m_confDiDatas.clear();
        for (int i = 0; i < m_ptCfg->m_yxNum; i++) {
            int no = m_ptCfg->m_yxStartIo + i;
            m_confDiDatas.append(DiData(no, tr("Point %1").arg(no), false));
        }
    }

    m_ptCfg->m_ycFrameType  = Util::hexString2Num(ui->edYcType->text());
    m_ptCfg->m_ycFuncode    = Util::hexString2Num(ui->edYcFuncode->text());
    m_ptCfg->m_ycNum        = ui->edYcNum->text().toInt();
    m_ptCfg->m_ycStartIo    = ui->edYcStartIo->text().toInt();
    if (ui->edYcNum->isEnabled()) {
        m_confAiDatas.clear();
        for (int i = 0; i < m_ptCfg->m_ycNum; i++) {
            int no = m_ptCfg->m_ycStartIo + i;
            m_confAiDatas.append(AiData(no, tr("Point %1").arg(no), 0));
        }
    }

    m_ptCfg->m_vyxFrameType = Util::hexString2Num(ui->edVYxType->text());
    m_ptCfg->m_vyxFuncode   = Util::hexString2Num(ui->edVYxFuncode->text());
    m_ptCfg->m_vyxNum       = ui->edVYxNum->text().toInt();
    m_ptCfg->m_vyxStartIo   = ui->edVYxStartIo->text().toInt();
    if (ui->edVYxNum->isEnabled()) {
        m_confVDiDatas.clear();
        for (int i = 0; i < m_ptCfg->m_vyxNum; i++) {
            int no = m_ptCfg->m_vyxStartIo + i;
            m_confVDiDatas.append(DiData(no, tr("Point %1").arg(no), false));
        }
    }

    m_ptCfg->m_ykReqType    = Util::hexString2Num(ui->edYkReqType->text());
    m_ptCfg->m_ykAckType    = Util::hexString2Num(ui->edYkAckType->text());
    m_ptCfg->m_ykReqCode    = Util::hexString2Num(ui->edYkReqCode->text());
    m_ptCfg->m_ykAckCode    = Util::hexString2Num(ui->edYkAckCode->text());
    m_ptCfg->m_ykExeCode    = Util::hexString2Num(ui->edYkExeCode->text());
    m_ptCfg->m_ykOpen       = Util::hexString2Num(ui->edYkOpen->text());
    m_ptCfg->m_ykClose      = Util::hexString2Num(ui->edYkClose->text());
    m_ptCfg->m_ykLock       = Util::hexString2Num(ui->edYkLock->text());
    m_ptCfg->m_ykUnlock     = Util::hexString2Num(ui->edYkUnlock->text());

    m_ptCfg->m_yxTime       = static_cast<uint>(ui->edYxTime->value());
    m_ptCfg->m_ycTime       = static_cast<uint>(ui->edYcTime->value());
    m_ptCfg->m_vyxTime      = static_cast<uint>(ui->edVYxTime->value());

    m_ptCfg->resetPoints(m_confDiDatas, m_confAiDatas, m_confVDiDatas);
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

void CDTSettingDlg::on_btnYxImportSheet_clicked()
{
    auto readLineDatas = readDataFromSelectedFile(ui->txtYxSheetInfo);
    if (readLineDatas.isEmpty()) {
        return ;
    }

    // 解析数据
    m_confDiDatas.clear();
    for (auto& lineData : readLineDatas) {
        // 无效则跳过该行数据
        if (!parseLineDataVaild(lineData)) {
            qInfo("Import yx sheet error:Read line data invaild!Please check you sheet file!");
            continue;
        }
        int noIdx = lineData.indexOf(' ');
        int ptNo = lineData.left(noIdx).toInt();
        int nameIdx = lineData.indexOf(',');
        QString ptName = lineData.mid(noIdx + 1, nameIdx - noIdx - 1);
        m_confDiDatas.append(DiData(ptNo, ptName, false));
    }
    ui->edYxNum->setText(QString::number(m_confDiDatas.size()));
    ui->edYxNum->setEnabled(false);
}

void CDTSettingDlg::on_btnYcImportSheet_clicked()
{
    auto readLineDatas = readDataFromSelectedFile(ui->txtYcSheetInfo);
    if (readLineDatas.isEmpty()) {
        return ;
    }

    // 解析数据
    m_confAiDatas.clear();

    for (auto& lineData : readLineDatas) {
        // 无效则跳过该行数据
        if (!parseLineDataVaild(lineData)) {
            qInfo("Import yc sheet error:Read line data invaild!Please check you sheet file!");
            continue;
        }
        int noIdx = lineData.indexOf(' ');
        int ptNo = lineData.left(noIdx).toInt();
        int nameIdx = lineData.indexOf(',');
        QString ptName = lineData.mid(noIdx + 1, nameIdx - noIdx - 1);
        m_confAiDatas.append(AiData(ptNo, ptName, 0.0));
    }
    ui->edYcNum->setText(QString::number(m_confAiDatas.size()));
    ui->edYcNum->setEnabled(false);
}

void CDTSettingDlg::on_btnVYxImportSheet_clicked()
{
    auto readLineDatas = readDataFromSelectedFile(ui->txtVYxSheetInfo);
    if (readLineDatas.isEmpty()) {
        return ;
    }

    // 解析数据
    m_confVDiDatas.clear();
    for (auto& lineData : readLineDatas) {
        // 无效则跳过该行数据
        if (!parseLineDataVaild(lineData)) {
            qInfo("Import virtual yx sheet error:Read line data invaild!Please check you sheet file!");
            continue;
        }
        int noIdx = lineData.indexOf(' ');
        int ptNo = lineData.left(noIdx).toInt();
        int nameIdx = lineData.indexOf(',');
        QString ptName = lineData.mid(noIdx + 1, nameIdx - noIdx - 1);
        m_confVDiDatas.append(DiData(ptNo, ptName, false));
    }
    ui->edVYxNum->setText(QString::number(m_confVDiDatas.size()));
    ui->edVYxNum->setEnabled(false);
}

QList<QByteArray> CDTSettingDlg::readDataFromSelectedFile(QLabel *infoLabel)
{
    // 读取所选文件的数据
    QList<QByteArray> readLineDatas;
    auto sheetFileName = getSheetFileName();
    if (sheetFileName.isEmpty()) {
        return readLineDatas;
    }

    try {
        readLineDatas = readFileData(sheetFileName);
        infoLabel->setText(QString("<font color=#0000FF>") + tr("Import success:") + sheetFileName + QString("</font>"));
    } catch (std::exception& e) {
        infoLabel->setText(QString("<font color=#FF0000>") + tr("Error:") + e.what() + QString("</font>"));
    }
    infoLabel->setHidden(false);// 显示导入提示信息
    return readLineDatas;
}

QString CDTSettingDlg::getSheetFileName()
{
    auto sysDocumentPaths = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    return QFileDialog::getOpenFileName(this, tr("Import Sheet"), sysDocumentPaths.first()
                                        , QLatin1String("All Files (*.*);;TXT(*.txt)"));

}

QList<QByteArray> CDTSettingDlg::readFileData(const QString &filename)
{
    QList<QByteArray> lineDatas;
    QFile file(filename);
    if (!file.open(QFile::ReadWrite)) {
        QString error = tr("Open file failed! ") + file.errorString();
        throw std::runtime_error(error.toStdString());
    }
    // 空文件异常
    if (file.atEnd()) {
        QString error = tr("File %1 is empty!").arg(filename);
        file.close();
        throw std::runtime_error(error.toStdString());
    }
    while (!file.atEnd()) {
        lineDatas.append(file.readLine());
    }
    file.close();
    return lineDatas;
}

bool CDTSettingDlg::parseLineDataVaild(const QByteArray &lineData)
{
    if (lineData.indexOf(' ') < 0 || lineData.indexOf(',') < 0) {
        return false;
    }
    auto spaceWord = lineData.split(' ');

    return !spaceWord.isEmpty() && QVariant(spaceWord.first()).canConvert<int>();
}
