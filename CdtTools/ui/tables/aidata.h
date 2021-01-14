#ifndef AIDATA_H
#define AIDATA_H

#include <QObject>

class AiData : public QObject
{
    Q_OBJECT
public:
    explicit AiData(QObject *parent = nullptr);
    explicit AiData(int io, const QString& name, int value, QObject *parent = nullptr);
    ~AiData() = default;

    AiData(const AiData& other);
    AiData& operator=(const AiData& other);
    AiData(AiData&& other) noexcept;
    AiData& operator=(AiData&& other) noexcept;

    inline void setIo(int io);
    inline int io() const;
    inline void setName(const QString& name);
    inline QString name() const;
    inline void setValue(int value);
    inline int value() const;

signals:

public slots:

private:
    int m_io{0};
    QString m_name{QString("Pt0")};
    int m_value{0};
};


inline void AiData::setIo(int io)
{
    m_io = io;
}

inline int AiData::io() const
{
    return m_io;
}

inline void AiData::setName(const QString &name)
{
    m_name = name;
}

inline QString AiData::name() const
{
    return m_name;
}

inline void AiData::setValue(int value)
{
    m_value = value;
}

inline int AiData::value() const
{
    return m_value;
}

#endif // AIDATA_H
