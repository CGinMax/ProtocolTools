#include "expandtile.h"
#include "ui_expandtile.h"
#include <QGridLayout>
#include <QFontMetrics>
#include <QMouseEvent>
ExpandTile::ExpandTile(const QString &title, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ExpandTile)
//    , m_icon(new TileIcon(QPixmap("/home/shijm/Documents/QtProject/ProtocolTools-Solution/PressPlateTool/resources/icons/down-arrow.png"),this))
    , m_checked(false)
    , m_editFilter(new EditableEventFilter(this))
{
    ui->setupUi(this);

//    m_icon->setAlignment(Qt::AlignRight);

    auto font = ui->editTitle->font();
    font.setBold(true);
    font.setPixelSize(14);
    ui->editTitle->setFont(font);
    ui->editTitle->setText(title);
//    ui->gridLayout->addWidget(m_icon, 0, 3);

    setEventFilter(ui->editTitle);
    connect(ui->btnQueryVersion, &QPushButton::clicked, this, &ExpandTile::queryVersion);
}

ExpandTile::~ExpandTile()
{

}

void ExpandTile::setTitle(const QString &title)
{
    ui->editTitle->setText(title);
}

void ExpandTile::setHardwareVersion(const QString &ver)
{
    ui->txtHardwareVer->setText(ver);
}

void ExpandTile::setSoftwareVersion(const QString &ver)
{
    ui->txtSoftwareVer->setText(ver);
}

void ExpandTile::setProductDescript(const QString &desc)
{
    ui->txtProductDesc->setText(desc);
//    QFontMetrics metrics(ui->txtProductDesc->font());
//    ui->txtProductDesc->setText(metrics.elidedText(desc, Qt::ElideRight, ui->txtProductDesc->width()));
}

void ExpandTile::setChecked(bool checked)
{
    if (m_checked == checked){
        return ;
    }
    m_checked = checked;
//    m_icon->rotateIcon(checked);
    emit toggled(checked);
}

bool ExpandTile::checked() const
{
    return m_checked;
}

void ExpandTile::setEventFilter(QLineEdit *edit)
{
    connect(edit, &QLineEdit::editingFinished, this, [=]{
        edit->setStyleSheet("background-color:transparent;");
        edit->setFrame(false);
        edit->setReadOnly(true);
        if (edit == ui->editTitle) {
            emit this->titleChanged(edit->text());
        }
    });
    emit edit->editingFinished();
    edit->installEventFilter(m_editFilter);
}

void ExpandTile::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        setChecked(!m_checked);
    }
    QWidget::mousePressEvent(event);
}
