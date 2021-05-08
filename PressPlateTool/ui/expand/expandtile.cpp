#include "expandtile.h"
#include "ui_expandtile.h"
#include <QGridLayout>
#include <QMouseEvent>
ExpandTile::ExpandTile(const QString &title, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ExpandTile)
    , m_icon(new TileIcon(QPixmap("/home/shijm/Documents/QtProject/ProtocolTools-Solution/PressPlateTool/resources/icons/down-arrow.png"),this))
    , m_checked(false)
    , m_editFilter(new EditableEventFilter(this))
{
    ui->setupUi(this);

    m_icon->setAlignment(Qt::AlignRight);

    auto font = ui->editTitle->font();
    font.setBold(true);
    font.setPixelSize(14);
    ui->editTitle->setFont(font);
    ui->editTitle->setText(title);
    ui->gridLayout->addWidget(m_icon, 0, 3);


    setEventFilter(ui->editTitle);
}

ExpandTile::~ExpandTile()
{

}

void ExpandTile::setTitle(const QString &title)
{
    ui->editTitle->setText(title);
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

void ExpandTile::setEventFilter(QLineEdit *edit)
{
    connect(edit, &QLineEdit::editingFinished, this, [=]{
        edit->setStyleSheet("background-color:transparent;");
        edit->setFrame(false);
        edit->setReadOnly(true);
    });
    edit->installEventFilter(m_editFilter);
}

void ExpandTile::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        setChecked(!m_checked);
    }
    QWidget::mousePressEvent(event);
}
