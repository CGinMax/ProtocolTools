#ifndef SERIALPORTPAGE_H
#define SERIALPORTPAGE_H

#include <QWidget>
#include "../../Communication/serialport.h"
#include "../protocol/protocolbase.h"
#include "cdtworkwidget.h"

class QVBoxLayout;
class SerialPortPage : public QWidget
{
    Q_OBJECT
public:
    explicit SerialPortPage(const QSharedPointer<SettingData>& settingData, QWidget *parent = nullptr);
    ~SerialPortPage() override;

    bool start();

    void stop();
signals:

public slots:
    void onUpdateData();
private:
    QSharedPointer<CommunicationBase> m_serialPort;
    QSharedPointer<SettingData> m_settingData;
    QScopedPointer<CDTWorkWidget> m_centerWidget;
    QVBoxLayout* m_layout;
};

#endif // SERIALPORTPAGE_H
