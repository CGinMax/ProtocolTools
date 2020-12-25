#ifndef NETWORKBASE_H
#define NETWORKBASE_H

#include <QObject>

class NetworkBase : public QObject
{
    Q_OBJECT
public:
    virtual ~NetworkBase();

    virtual void open() = 0;
    virtual void close() = 0;
    virtual bool write(const QByteArray& data) = 0;
    virtual QByteArray read() = 0;
    virtual bool isActived() = 0;

signals:
    void connected();
    void disconnected();
    void recvData(const QByteArray& data);
};

#endif // NETWORKBASE_H
