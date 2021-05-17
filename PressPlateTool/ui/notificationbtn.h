#ifndef NOTIFICATIONBTN_H
#define NOTIFICATIONBTN_H

#include <QWidget>
#include <QPushButton>

class NotificationBtn : public QPushButton
{
    Q_OBJECT
public:
    explicit NotificationBtn(const QString& text = QString("Notification"), QWidget *parent = nullptr);
    ~NotificationBtn() override;

    void setHasNewNotification(bool hasNew);

protected:
    bool event(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
signals:
    void showNotification();
    void hideNotification();

public slots:

private:
    bool m_hasNew;
};

#endif // NOTIFICATIONBTN_H
