#include "expandtile.h"
#include <QGridLayout>
#include <QMouseEvent>

ExpandTile::ExpandTile(const QString &title, QWidget *parent)
    : QWidget(parent)
    , m_title(new QLabel(this))
    , m_icon(new QLabel(this))
    , m_checked(false)
{
    m_icon->setText("aaa");
    m_title->setTextFormat(Qt::TextFormat::RichText);
    m_title->setText(QString("<b>%1</b>").arg(title));
    auto mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(4);
    mainLayout->addWidget(m_icon, 0, 0 );
    mainLayout->addWidget(m_title, 0, 1);
    auto subTitle = new QLabel("subtitle", this);
    mainLayout->addWidget(subTitle, 1, 1);
}

ExpandTile::~ExpandTile()
{

}

void ExpandTile::setTitle(const QString &title)
{
    m_title->setText(QString("<b>%1</b>").arg(title));
}

void ExpandTile::setChecked(bool checked)
{
    if (m_checked == checked){
        return ;
    }
    m_checked = checked;
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
