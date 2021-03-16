#include "qtmaterialdropdownbutton.h"
#include "qtmaterialdropdownbutton_p.h"
#include "lib/qtmaterialstyle.h"
#include <QEvent>
#include <QTimer>
#include <QPainter>
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QFrame>
#include <QtWidgets/QVBoxLayout>
QtMaterialDropDownButtonPrivate::QtMaterialDropDownButtonPrivate(QtMaterialDropDownButton *q)
    : QtMaterialRaisedButtonPrivate (q)
{

}

QtMaterialDropDownButtonPrivate::~QtMaterialDropDownButtonPrivate()
{}

void QtMaterialDropDownButtonPrivate::init()
{
    Q_Q(QtMaterialDropDownButton);

    frame = new QFrame();
    listview = new QWidget();
    viewLayout = new QVBoxLayout();

    frame->setParent(q->parentWidget());
    listview->setParent(q->parentWidget());

    auto effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(11);
    effect->setColor(QColor(0, 0, 0, 50));
    effect->setOffset(0, 3);

    frame->setGraphicsEffect(effect);
    frame->setVisible(false);

    listview->setLayout(viewLayout);
    listview->setVisible(false);

    viewLayout->setContentsMargins(0, 0, 0, 0);
    viewLayout->setSpacing(0);

    QObject::connect(q, &QAbstractButton::clicked, q, &QtMaterialDropDownButton::showPopup);
}

QtMaterialDropDownButton::QtMaterialDropDownButton(QWidget *parent)
    : QtMaterialRaisedButton(*new QtMaterialDropDownButtonPrivate(this), parent)
{
    d_func()->init();
}

void QtMaterialDropDownButton::addItem(const QString &text, const QVariant &userData)
{
    m_textList.append(qMakePair(text, userData));
}

void QtMaterialDropDownButton::addItem(const QIcon &icon, const QString &text, const QVariant &userData)
{
    m_textList.append(qMakePair(text, userData));
}

void QtMaterialDropDownButton::addItems(const QStringList &texts)
{
    for (auto&& text : texts) {
        m_textList.append(qMakePair(text, QVariant()));
    }
}

QtMaterialDropDownButton::QtMaterialDropDownButton(QtMaterialDropDownButtonPrivate &d, QWidget *parent)
{
    d_func()->init();
}

bool QtMaterialDropDownButton::event(QEvent *event)
{
    Q_D(QtMaterialDropDownButton);

    switch (event->type()) {
    case QEvent::Move:
    case QEvent::Resize: {
        d->listview->move(pos() + QPoint(0, height() + 6));
        break;
    }
    case QEvent::ParentChange: {
        auto widget = static_cast<QWidget *>(parent());
        if (widget) {
            d->listview->setParent(widget);
            d->frame->setParent(widget);
        }
        break;
    }
    default:
        break;
    }

    return QtMaterialRaisedButton::event(event);
}

bool QtMaterialDropDownButton::eventFilter(QObject *watched, QEvent *event)
{
    Q_D(QtMaterialDropDownButton);

    if (d->frame == watched)
    {
        switch (event->type())
        {
        case QEvent::Paint: {
            QPainter painter(d->frame);
            painter.fillRect(d->frame->rect(), Qt::white);
            break;
        }
        default:
            break;
        }
    }
    else if (d->listview == watched)
    {
        switch (event->type())
        {
        case QEvent::Resize:
        case QEvent::Move: {
            d->frame->setGeometry(d->listview->geometry());
            break;
        }
        case QEvent::Show: {
            d->frame->show();
            d->listview->raise();
            break;
        }
        case QEvent::Hide: {
            d->frame->hide();
            break;
        }
        default:
            break;
        }
    }
    else
    {
        switch (event->type())
        {
        case QEvent::MouseButtonPress: {
//            emit d->stateMachine->shouldFade();
            d->frame->show();
            QtMaterialFlatButton *widget;
            if ((widget = static_cast<QtMaterialFlatButton *>(watched))) {
                QString text(widget->text());
                setText(text);
//                m_currentIndex = d->listview->in
                emit currentTextChanged(text);
            }
            break;
        }
        default:
            break;
        }
    }
    return QtMaterialRaisedButton::eventFilter(watched, event);
}

void QtMaterialDropDownButton::showPopup()
{
    if (m_textList.isEmpty()) {
        return ;
    }


//    Q_D(QtMaterialDropDownButton);
//    auto btn = qobject_cast<QtMaterialFlatButton*>(d->viewLayout->itemAt(m_currentIndex)->widget());
//    btn->setBackgroundColor(QtMaterialStyle::instance().themeColor("primary3"));

}

void QtMaterialDropDownButton::updateRect()
{
    Q_D(QtMaterialDropDownButton);

    while (d->viewLayout->count() > 0) {
        auto widget = d->viewLayout->itemAt(0)->widget();
        if (widget) {
            d->viewLayout->removeWidget(widget);
            delete widget;
        }
    }

    for (auto&& text : m_textList) {
        auto item = new QtMaterialFlatButton;
        item->setTextAlignment(Qt::AlignLeft);
        item->setCornerRadius(0);
        item->setHaloVisible(false);
        item->setFixedHeight(40);
        item->setOverlayStyle(Material::TintedOverlay);
        d->viewLayout->addWidget(item);

    }

    d->listview->setFixedHeight(m_textList.size() * 40);
    d->listview->setFixedWidth(width());
    d->listview->update();
}
