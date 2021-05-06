#include "expandtile.h"
#include "ui_expandtile.h"
#include <QGridLayout>
#include <QMouseEvent>
ExpandTile::ExpandTile(const QString &title, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ExpandTile)
    , m_icon(new TileIcon(this))
    , m_checked(false)
{
    ui->setupUi(this);
    m_icon->setPixmap(QPixmap("/home/shijm/Documents/QtProject/ProtocolTools-Solution/PressPlateTool/resources/icons/down-arrow.png"));
    m_icon->setAlignment(Qt::AlignRight);

    ui->txtTitle->setTextFormat(Qt::TextFormat::RichText);
    ui->txtTitle->setText(QString("<b>%1</b>").arg(title));
    ui->gridLayout->addWidget(m_icon, 0, 3);
}

ExpandTile::~ExpandTile()
{

}

void ExpandTile::setTitle(const QString &title)
{
    ui->txtTitle->setText(QString("<b>%1</b>").arg(title));
}

void ExpandTile::setChecked(bool checked)
{
    if (m_checked == checked){
        return ;
    }
    m_checked = checked;
    m_icon->rotateIcon(checked);
    emit toggled(checked);
}

bool ExpandTile::checked() const
{
    return m_checked;
}

void ExpandTile::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        setChecked(!m_checked);
    }
    QWidget::mousePressEvent(event);
}
