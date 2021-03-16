#ifndef QTMATERIALDROPDOWNBUTTON_H
#define QTMATERIALDROPDOWNBUTTON_H

#include "qtmaterialraisedbutton.h"
#include <QtCore/QVariant>

class QtMaterialDropDownButtonPrivate;
class QtMaterialDropDownButton : public QtMaterialRaisedButton
{
    Q_OBJECT
public:
    explicit QtMaterialDropDownButton(QWidget *parent = nullptr);

    void addItem(const QString& text, const QVariant& userData = QVariant());

    void addItem(const QIcon& icon, const QString& text, const QVariant& userData = QVariant());

    void addItems(const QStringList& texts);

    int currentIndex() const;
    QVariant currentData() const;
    QString currentText() const;
protected:
    QtMaterialDropDownButton(QtMaterialDropDownButtonPrivate &d, QWidget *parent = 0);

    bool event(QEvent *event) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

signals:
    void currentIndexChanged(int index);

    void currentTextChanged(const QString& text);

public slots:
    void showPopup();

private:
    void updateRect();

private:
    Q_DISABLE_COPY(QtMaterialDropDownButton)
    Q_DECLARE_PRIVATE(QtMaterialDropDownButton)
    int m_currentIndex;
    QList<QPair<QString, QVariant>> m_textList;
};

#endif // QTMATERIALDROPDOWNBUTTON_H
