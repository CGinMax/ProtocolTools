#ifndef NETWORKBASE_H
#define NETWORKBASE_H

#include <QObject>

class NetworkBase : public QObject
{
    Q_OBJECT
public:
    virtual ~NetworkBase();

    virtual bool open() = 0;
    virtual bool open(const QString& ip, ushort port) = 0;
    virtual void close() = 0;
    virtual bool write(const char* data, int size) = 0;
    virtual bool write(const QByteArray& data) = 0;
    virtual int read(char* data, int size) = 0;
    virtual QByteArray readAll() = 0;
    virtual bool isActived() = 0;
    virtual QString toString() = 0;

signals:
    void connected();
    void disconnected();
    void readyRead();
    void recvData(const QByteArray& data);
    void showMessage(const QString& msg);

public slots:
    virtual void writeData(const QByteArray& data) = 0;
};

#endif // NETWORKBASE_H
